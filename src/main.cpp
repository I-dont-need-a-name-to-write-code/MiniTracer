#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

int main(void) {
    uint32_t seed = time(NULL);
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    std::cout << random_in_unit_hemisphere(seed, vec3(0, 0, 1)) << std::endl;
    return 0;
}
