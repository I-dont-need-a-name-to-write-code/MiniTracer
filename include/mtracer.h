#ifndef MINI_TRACER_H
#define MINI_TRACER_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>

#include "./mmath.h"
#include "./mcamera.h"
#include "./mobject.h"

class Scene {
public:
    Scene() = default;
    void add_object(const Sphere &sphere);
    void add_object(const Triangle &triangle);
public:
    std::vector<Object> m_objects;
};

class Mini_Tracer {
public:
    Mini_Tracer(uint32_t width, uint32_t height, 
                const point3 &cam_o, const vec3 &cam_look_at, float vfov, 
                const Scene *p_scene,
                uint32_t max_bounces, uint32_t max_samples);
    
    void render();
    void postprocess();
    void save_as_ppm(const char *file_path);

    ~Mini_Tracer();

private:
    void per_pixel(color3 &fragColor, const vec2 &fragCoord);
    color3 trace_ray(const ray &r, uint32_t &rng_state);
    Hit_Info check_ray_collision(const ray &r);
    
private:
    // color3 -> < red range [0, 1], green range [0, 1], blue range [0, 1] >
    color3  *img_buffer;  
    float    aspect_ratio;
    uint32_t width;
    uint32_t height;
    Camera   camera;
    const Scene *p_scene;
    uint32_t max_bounces;
    uint32_t max_samples;
};

#endif // MINI_TRACER_H
