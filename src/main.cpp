#include <iostream>

#include "../include/mtracer.h"

int main(void) {

    const uint32_t width  = 1280;
    const uint32_t height = 720;
    const point3   cam_origin  = point3(0, 0.5, -2);
    const vec3     cam_look_at = vec3(0, 0, 0); 
    const float    vfov = deg_to_rad(90);
    const uint32_t max_bounces = 10;
    const uint32_t max_samples = 100;

    Emissive e1(color3(1.0), 2.0);
    Sphere sphereA(point3(15, 10, -3), 10);
    sphereA.set_material(Material_Type::EMISSIVE, &e1);

    Lambertian l1(color3(1, 0.6, 0.1));
    Sphere sphereB(point3(0, 0, 0), 0.5); 
    sphereB.set_material(Material_Type::LAMBERTIAN, &l1);

    Lambertian l2(color3(0.2, 0.7, 0.5));
    Sphere sphereC(point3(0, -100.5, 0), 100); 
    sphereC.set_material(Material_Type::LAMBERTIAN, &l2);

    Scene scene; 
    scene.add_object(sphereA);
    scene.add_object(sphereB);
    scene.add_object(sphereC);

    Mini_Tracer mt(
        width, height, 
        cam_origin, cam_look_at, vfov, 
        &scene,
        max_bounces, max_samples
    );

    mt.render();
    mt.postprocess();
    mt.save_as_ppm("./render/image.ppm");

    return 0;
}
