#include <iostream>
#include "../include/mini_math.h"

using namespace mini_math;

int main(void) {
    srand(time(NULL));
    
    vec3 i { 1, -1, 0 };
    vec3 n { 0, 1, 0 };

    std::cout << reflect(i, n) << std::endl;

    return 0;
}
