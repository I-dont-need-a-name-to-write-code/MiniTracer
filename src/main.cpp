#include <iostream>

#include "../include/mtracer.h"

int main(void) {
    const char *file_path = "./render/image.ppm";
    const size_t width  = 1280;
    const size_t height = 720;
    Mini_Tracer mt
    (
            width, height,
            vec3(0, 0, 0), vec3(0, 0, -1), deg_to_rad(90)
    );
    mt.render_scene();
    mt.postprocess();
    mt.save_as_ppm(file_path);
    return 0;
}
