#include <iostream>
#include <fstream>

#include "../include/mtracer.h"

int main(void) {

    const uint32_t width  = 1280;
    const uint32_t height = 720;
    const point3   cam_origin  = point3(0, 0.5, -2);
    const vec3     cam_look_at = vec3(0, 0, 0); 
    const float    vfov = deg_to_rad(90);
    const uint32_t max_bounces = 10;
    const uint32_t max_samples = 1000;

    Material m1;
    m1.albedo            = color3(0.7, 0.4, 0.3);  
    m1.emission_color    = color3(0.0f); 
    m1.emission_strength = 0.0f;

    Material m2;
    m2.albedo            = color3(0.2, 0.7, 0.5);  
    m2.emission_color    = color3(0.0f); 
    m2.emission_strength = 0.0f;

    Material mem;
    mem.albedo            = color3(0.0f);  
    mem.emission_color    = color3(1.0f); 
    mem.emission_strength = 10.0f;

    Scene scene;

    Sphere sphereA(point3(10, 10, 20), 10, &mem); 
    scene.add_object(Object_Type::SPHERE, &sphereA);

    Sphere sphereB(point3(0, 0, 0), 0.5, &m1);
    scene.add_object(Object_Type::SPHERE, &sphereB);

    Sphere sphereC(point3(0, -100.5, 0), 100, &m2);
    scene.add_object(Object_Type::SPHERE, &sphereC);
    
    Mini_Tracer mt(
        width, height, 
        cam_origin, cam_look_at, vfov, 
        &scene,
        max_bounces, max_samples
    );

    mt.render();
    mt.preprocess();
    mt.save_as_ppm("./render/image.ppm");

    return 0;
}
