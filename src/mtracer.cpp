#include "../include/mtracer.h"

void MiniTracer::per_pixel(color3 &fragColor, const vec2 &fragCoord) {
    float r = fragCoord.x() / this->width;
    float g = fragCoord.y() / this->height;
    float b = 0.5;
    fragColor = color3(r, g, b);
}

MiniTracer::MiniTracer(uint32_t width, uint32_t height) {
    this->width  = width;
    this->height = height;
    this->img_buffer   = new color3[width * height];
    this->aspect_ratio = (float)width / (float)height;
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
