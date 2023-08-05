#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
 
    float r = deg_to_rad(360 + 45);

    matrix44 a (
        cosf(r), -sinf(r), 0, 0,
        sinf(r),  cosf(r), 0, 0,
              0,        0, 1, 0,
              0,        0, 0, 1
    );

    vec3 v(1, 0, 0);
    vec3 changed_v = (a * v);

    std::cout << "v              = " << v << std::endl;
    std::cout << "v1 = (mat * v) = " << changed_v << std::endl;

    optional<matrix44> inv_a = inverse(a);
    if(inv_a.type == SOME) {
        std::cout << "(inv_mat * v1) = " << (inv_a.result * changed_v) << std::endl;  
    } else {
        std::cout << "NONE!\n";
    }


    return 0;
}
