#include <iostream>
#include "../include/mini_math.h"

using namespace mmath;

static uint32_t r_seed = time(NULL);

int main(void) {
 
    // imaging a plane pointing in the x direction
    float X = deg_to_rad(90);
    float Y = deg_to_rad(180);
    float Z = deg_to_rad(45);

    vec3 v (1, 1, 1);
    mat4x4 rotateXYZ = mat4x4::rotateX(X) * mat4x4::rotateY(Y) * mat4x4::rotateZ(Z);

    vec3 changed_v = (rotateXYZ * v);

    std::cout << "v              = " << v << std::endl;
    std::cout << "v1 = (mat * v) = " << changed_v << std::endl;

    optional<mat4x4> inv_rotateXYZ = mat4x4::inverse(rotateXYZ);
    if(inv_rotateXYZ.type == result_type::SOME) {
        std::cout << "(inv_mat * v1) = " << (inv_rotateXYZ.result * changed_v) << std::endl;  
    } else {
        std::cout << "NONE!\n";
    }


    return 0;
}
