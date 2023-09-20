#include "../include/mtracer.h"

void Mini_Tracer::per_pixel(color3 &fragColor, const vec2 &fragCoord) {
    float u = fragCoord.x() / (this->width  - 1); // [0, 1]
    float v = fragCoord.y() / (this->height - 1); // [0, 1]
    float su = (u * 2.0f) - 1.0f;          // [-1, 1]
    float sv = ((1.0f - v) * 2.0f) - 1.0f; // [1, -1]
    ray r = camera.get_ray(su, sv);
    fragColor = trace_ray(r);
}

color3 Mini_Tracer::trace_ray(const ray &r) {

    Hit_Info info = check_ray_collision(r);
    if(info.is_hit) {
        const Material *p_mat = info.p_mat;
        return p_mat->albedo;
    }   

    return color3(0.1, 0.1, 0.1);
}

Hit_Info Mini_Tracer::check_ray_collision(const ray &r) {

    Hit_Info result;
    result.is_hit = false;
    Hit_Info hit_info;
    float min_t = std::numeric_limits<float>::max();
    
    const std::vector<Object> &objs = this->p_scene->objects;
    for(uint32_t i = 0; i < objs.size(); ++i) {

        const Object &obj = objs[i];
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
    this->objects.emplace_back(type, p_obj);
}

Mini_Tracer::Mini_Tracer(uint32_t width, uint32_t height, const point3 &cam_o, 
                         const vec3 &cam_look_at, float vfov, const Scene *p_scene) 
{
    this->width  = width;
    this->height = height;
    this->img_buffer   = new color3[width * height];
    this->aspect_ratio = (float)width / (float)height;
    this->camera = Camera(cam_o, cam_look_at, vfov, this->aspect_ratio);
    this->p_scene = p_scene;
}

void Mini_Tracer::render() {
    for(uint32_t y = 0; y < this->height; ++y) {
        for(uint32_t x = 0; x < this->width; ++x) {
            per_pixel(this->img_buffer[x + y * width], vec2(x, y));
        }
    }
}

void Mini_Tracer::save_as_ppm(const char *file_path) {
    std::ofstream img(file_path);
    if(!img.is_open()) {
        std::cerr << "[ERR -> COULD NOT OPEN FILE : " << file_path << "]\n";
        return;
    }
    img << "P3\n" << this->width << " " << this->height << "\n255\n";
    for(uint32_t i = 0; i < this->width * this->height; ++i) {
        color3 rgb = vec3::clamp(this->img_buffer[i], 0.0f, 1.0f);
        img << (uint32_t)(rgb.x() * 255.0f) << " " 
            << (uint32_t)(rgb.y() * 255.0f) << " " 
            << (uint32_t)(rgb.z() * 255.0f) << "\n";
    }   
    img.close();
}

Mini_Tracer::~Mini_Tracer() {
    delete [] this->img_buffer;
}
