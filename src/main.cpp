#include <iostream>
#include "../include/mini_math.h"

using namespace mmath;

static uint32_t r_seed = time(NULL);

int main(void) {
 
    float r = deg_to_rad(-90);

    vec3 v (1, 1, 1);
    mat4x4 a = mat4x4::rotateX(r);
    vec3 changed_v = (a * v);

    std::cout << "v              = " << v << std::endl;
    std::cout << "v1 = (mat * v) = " << changed_v << std::endl;

    optional<mat4x4> inv_a = mat4x4::inverse(a);
    if(inv_a.type == result_type::SOME) {
        std::cout << "(inv_mat * v1) = " << (inv_a.result * changed_v) << std::endl;  
    } else {
        std::cout << "NONE!\n";
    }


    return 0;
}
