#include <iostream>
#include <fstream>

#include "../include/mtracer.h"

int main(void) {

    uint32_t width  = 1280;
    uint32_t height = 720;
    
    MiniTracer mt(width, height);
    mt.render();
    mt.save_as_ppm("./render/image.ppm");

    return 0;
}
