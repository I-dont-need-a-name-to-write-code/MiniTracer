#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
 
    vec3 a = {
        1, 
        2, 
        3
    };

    Matrix4x4 t_m (
        1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1,
        0, 0, 0, 1
    );

    vec3 t_a = t_m * a;

    std::cout << a << std::endl;
    std::cout << t_a << std::endl;


    return 0;
}
