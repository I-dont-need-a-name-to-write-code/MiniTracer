#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
    
    Matrix4x4 matrix1 (
        1, 2, 3, 4,
        3, 4 ,1, 2,
        4, 4, 4, 4,
        3, 4 ,1, 2
    );

    Matrix4x4 matrix2;
    
    std::cout << matrix1 << std::endl;
    std::cout << matrix2 << std::endl;

    matrix1 = matrix2;

    std::cout << matrix1 << std::endl;
    std::cout << matrix2 << std::endl;

    return 0;
}
