#include <iostream>
#include "../include/vec3.h"

using namespace vec_math;

int main(void) {
    srand(time(NULL));
    vec3 a{ -1, -1, -1 };
    vec3 b = -a;
    std::cout << lerp(a, b, 0.0) << std::endl;
    std::cout << lerp(a, b, 0.25) << std::endl;
    std::cout << lerp(a, b, 0.5) << std::endl;
    std::cout << lerp(a, b, 0.75) << std::endl;
    std::cout << lerp(a, b, 1.0) << std::endl;
    return 0;
}
