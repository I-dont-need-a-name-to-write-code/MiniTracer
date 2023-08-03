#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
 
    Matrix4x4 translate (
        10,  0,  0,  10,
         0, 10,  0,  10,
         0,  0, 10,  10,
         0,  0,  0,  10
    );

    vec3 v = {
        1, 2, 3
    };

    std::cout << translate * v << std::endl;

    return 0;
}
