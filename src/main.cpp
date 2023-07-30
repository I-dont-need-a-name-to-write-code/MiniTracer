#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

int main(void) {
    uint32_t seed = time(NULL);
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    std::cout << rand_float(seed) << std::endl;
    return 0;
}
