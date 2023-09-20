#include <iostream>
#include <fstream>

#include "../include/mtracer.h"

int main(void) {

    const uint32_t width  = 1280;
    const uint32_t height = 720;
    const point3 cam_origin  = point3(0, 0.5, 0);
    const vec3   cam_look_at = vec3(0, 0.5, 1); 
    const float  vfov = deg_to_rad(90);
 
    Scene scene;
    Material mred   = (Material){ color3(1, 0, 0) }; 
    Material mgreen = (Material){ color3(0, 1, 0) };

    Sphere sphereA(point3(0, 0.5, 2), 0.5, &mred); 
    scene.add_object(Object_Type::SPHERE, &sphereA);

    Sphere sphereB(point3(0, -100, 2), 100, &mgreen);
    scene.add_object(Object_Type::SPHERE, &sphereB);
    
    Mini_Tracer mt(width, height, cam_origin, 
                   cam_look_at, vfov, &scene);

    mt.render();
    mt.save_as_ppm("./render/image.ppm");
    

    return 0;
}
