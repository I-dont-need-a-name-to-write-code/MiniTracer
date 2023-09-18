#include <iostream>
#include <fstream>

#include "../include/mtracer.h"

int main(void) {

    const uint32_t width  = 1280;
    const uint32_t height = 720;
    const point3 cam_origin = point3(0, 0, -1);
    const vec3 cam_look_at = vec3(0, 0, 0); 
    const float vfov = deg_to_rad(90);
    
    Mini_Tracer mt(width, height, 
                   cam_origin, cam_look_at, vfov);
    mt.render();
    mt.save_as_ppm("./render/image.ppm");
    

    return 0;
}
