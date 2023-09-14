#include <iostream>
#include <fstream>

#include "../include/mmath.h"
using namespace mmath;

static uint32_t r_seed = time(NULL);

void save_as_ppm(const char *file_path, const uint32_t *img_buffer, 
                 const uint32_t width,  const uint32_t height) 
{
    // color format => 32-bit ABGR
    std::ofstream img(file_path);
    if(!img.is_open()) {
        std::cerr << "[ERR -> COULD NOT OPEN FILE : " << file_path << "]\n";
        return;
    }
    img << "P3\n" << width << " " << height << "\n255\n";
    for(uint32_t i = 0; i < width * height; ++i) {
        uint32_t col = img_buffer[i];
        uint32_t rgb[] = {
            ((col >> 0)  & 0x000000FF),
            ((col >> 8)  & 0x000000FF),
            ((col >> 16) & 0x000000FF),
        };
        img << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
    }   
    img.close();
}


int main(void) {

    float aspect_ratio = 16.0f / 9.0f;
    uint32_t height = 720;
    uint32_t width  = height * aspect_ratio;
    
    uint32_t *img_buffer = new uint32_t[width * height];

    for(uint32_t i = 0; i < height; ++i) {
        for(uint32_t j = 0; j < width; ++j) {

            uint32_t r = (uint32_t)randf(r_seed, 0, 255);
            uint32_t g = (uint32_t)randf(r_seed, 0, 255);
            uint32_t b = (uint32_t)randf(r_seed, 0, 255);
            img_buffer[i * width + j] = 0xFF000000 | (b << 16) | (g << 8) | r;

        }
    }

    save_as_ppm("./render/image.ppm", img_buffer, width, height);
    delete [] img_buffer;

    return 0;
}
