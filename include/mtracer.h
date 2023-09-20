#ifndef MINI_TRACER_H
#define MINI_TRACER_H

#include <iostream>
#include <fstream>

#include "./mmath.h"
#include "./mcamera.h"
#include "./mobject.h"

class Mini_Tracer {
public:
    Mini_Tracer(uint32_t width, uint32_t height,
                const point3 &cam_o, const vec3 &cam_look_dir, float vfov);
    void render();
    void save_as_ppm(const char *file_path);
    ~Mini_Tracer();

private:
    color3 trace_ray(const ray &r);
    void per_pixel(color3 &fragColor, const vec2 &fragCoord);
    
private:
    // color3 -> < red range [0, 1], green range [0, 1], blue range [0, 1] >
    color3  *img_buffer;  
    float    aspect_ratio;
    uint32_t width;
    uint32_t height;
    Camera   camera;
};

#endif // MINI_TRACER_H


