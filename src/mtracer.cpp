#include "../include/mtracer.h"

void Mini_Tracer::per_pixel(color3 &fragColor, const vec2 &fragCoord) {
    uint32_t rng_state = (uint32_t(fragCoord.x()) * 1973) + 
                         (uint32_t(fragCoord.y()) * 9277);
    ray r;
    float u, v, su, sv;
    color3 total_light = color3(0);
    for(uint32_t sample_pass = 0; sample_pass < this->max_samples; ++sample_pass) 
    {
        u  = (fragCoord.x() + randf(rng_state, 0.0f, 1.0f)) / float(this->width  - 1); // [0, 1]
        v  = (fragCoord.y() + randf(rng_state, 0.0f, 1.0f)) / float(this->height - 1); // [0, 1]
        su = (u * 2.0f) - 1.0f;          // [-1, 1]
        sv = ((1.0f - v) * 2.0f) - 1.0f; // [1, -1]
        r  = camera.get_ray(su, sv);
        total_light = total_light + this->trace_ray(r, rng_state);
    }
    fragColor = total_light / float(this->max_samples);
}

color3 Mini_Tracer::trace_ray(const ray &r, uint32_t &rng_state) {
    color3 ray_color      = color3(1.0f);
    color3 incoming_light = color3(0.0f);
    ray curr_ray = r;
    for(uint32_t i = 0; i <= this->max_bounces; ++i) {
        Hit_Info info = this->check_ray_collision(curr_ray);
        if(info.is_hit) {
            const Material *p_mat = info.p_mat;
            color3 emission = p_mat->emission_strength * p_mat->emission_color;
            incoming_light = incoming_light + (ray_color * emission);
            ray_color = ray_color * p_mat->albedo;
            curr_ray = ray( (info.hit_point + info.normal * 0.01),
                            vec3::normalize(info.normal + random_in_unit_sphere(rng_state)) );
        } else {
            break;
        }
    }
    return incoming_light;
}

Hit_Info Mini_Tracer::check_ray_collision(const ray &r) {
    Hit_Info result;
    result.is_hit = false;
    Hit_Info hit_info;
    float min_t = std::numeric_limits<float>::max();
    
    for(const Object &obj : this->p_scene->m_objects) {
        Sphere sphere = *(Sphere*)obj.p_obj;
        hit_info = Sphere::hit(sphere, r);
    
        if(!hit_info.is_hit) continue;

        if(hit_info.t < min_t) {
            min_t = hit_info.t;
            result = hit_info;
        }   
    }
    return result; 
}

void Scene::add_object(Object_Type type, void *p_obj) {
    this->m_objects.emplace_back(type, p_obj);
}

Mini_Tracer::Mini_Tracer(uint32_t width, uint32_t height, 
                         const point3 &cam_o, const vec3 &cam_look_at, float vfov, 
                         const Scene *p_scene,
                         uint32_t max_bounces, uint32_t max_samples)
{                                                                                  
    this->width  = width;
    this->height = height;
    this->img_buffer   = new color3[width * height];
    this->aspect_ratio = (float)width / (float)height;
    this->camera = Camera(cam_o, cam_look_at, vfov, this->aspect_ratio);
    this->p_scene = p_scene;
    this->max_bounces = max_bounces;
    this->max_samples = max_samples;
}

void Mini_Tracer::render() {
    std::cerr << "[INFO] Starting Render...\n";
    for(uint32_t y = 0; y < this->height; ++y) 
    {
        uint32_t p = uint32_t(((float)y / (float)(this->height - 1)) * 100.0f);
        if(p % 5 == 0) std::cerr << "\r[INFO] Progress -> " << p << "%" << std::flush;
        for(uint32_t x = 0; x < this->width; ++x) 
        {
            per_pixel(this->img_buffer[x + y * width], vec2(float(x), float(y)));
        }
    }
}

void Mini_Tracer::postprocess() {
    // gamma 2.0 maybe???
    for(uint32_t i = 0; i < this->width * this->height; ++i) {
        color3 &color = this->img_buffer[i];
        color.x() = M_SQRT(color.x());
        color.y() = M_SQRT(color.y());
        color.z() = M_SQRT(color.z());
    }
}

void Mini_Tracer::save_as_ppm(const char *file_path) {
    std::ofstream img(file_path);
    if(!img.is_open()) {
        std::cerr << "[ERROR] COULD NOT OPEN FILE : " << file_path << "\n";
        return;
    }
    img << "P3\n" << this->width << " " << this->height << "\n255\n";
    for(uint32_t i = 0; i < this->width * this->height; ++i) {
        color3 rgb = vec3::clamp(this->img_buffer[i], 0.0f, 1.0f);
        img << static_cast<uint32_t>(rgb.x() * 255.999f) << " " 
            << static_cast<uint32_t>(rgb.y() * 255.999f) << " " 
            << static_cast<uint32_t>(rgb.z() * 255.999f) << "\n";
    }   
    img.close();
}

Mini_Tracer::~Mini_Tracer() {
    delete [] this->img_buffer;
}
