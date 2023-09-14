#ifndef MINI_TRACER_H
#define MINI_TRACER_H

#include <iostream>
#include <fstream>

#include "./mmath.h"

class MiniTracer {
public:
    MiniTracer(uint32_t width, uint32_t height);
    void render();
    void save_as_ppm(const char *file_path);
    ~MiniTracer();

private:
    void per_pixel(color3 &fragColor, const vec2 &fragCoord);
    
private:
    color3  *img_buffer;
    float    aspect_ratio;
    uint32_t width;
    uint32_t height;
};

#endif // MINI_TRACER_H


