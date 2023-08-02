#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
 
    Matrix4x4 a (
        5,  7, 9, 10,
        2,  3, 3,  8,
        8, 10, 2,  3,
        3,  3, 4,  8 
    );

    Matrix4x4 b (
        3,  10, 12, 18,
        12,  1,  4,  9,
        9,  10, 12,  2,
        3,  12,  4, 10
    );

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    Matrix4x4 add = a + b;
    Matrix4x4 sub = a - b;
    Matrix4x4 mul = a * b;

    std::cout << add << std::endl;
    std::cout << sub << std::endl;
    std::cout << mul << std::endl;


    return 0;
}
