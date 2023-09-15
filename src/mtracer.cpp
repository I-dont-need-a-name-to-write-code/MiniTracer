#include "../include/mtracer.h"

void MiniTracer::per_pixel(color3 &fragColor, const vec2 &fragCoord) {
    float u = fragCoord.x() / (this->width  - 1); // [0, 1]
    float v = fragCoord.y() / (this->height - 1); // [0, 1]

    float su = (u * 2.0f) - 1.0f;          // [-1, 1]
    float sv = ((1.0f - v) * 2.0f) - 1.0f; // [1, -1]
    ray r = camera.get_ray(su, sv);

    float dy = r.dir().y();
    float t = (dy + 1.0f) * 0.5f;

    fragColor = vec3::lerp(color3(1, 1, 1), color3(0.5, 0.7, 1.0), t);
}

MiniTracer::MiniTracer(uint32_t width, uint32_t height, 
                       const point3 &cam_o, const vec3 &cam_look_dir, float vfov) 
{
    this->width  = width;
    this->height = height;
    this->img_buffer   = new color3[width * height];
    this->aspect_ratio = (float)width / (float)height;
    this->camera = Camera(cam_o, cam_look_dir, vfov, this->aspect_ratio);
}

void MiniTracer::render() {
    for(uint32_t y = 0; y < this->height; ++y) {
        for(uint32_t x = 0; x < this->width; ++x) {
            per_pixel(this->img_buffer[x + y * width], vec2(x, y));
        }
    }
}

void MiniTracer::save_as_ppm(const char *file_path) {
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

MiniTracer::~MiniTracer() {
    delete [] this->img_buffer;
}
