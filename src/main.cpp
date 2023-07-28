#include <iostream>
#include "../include/vec3.h"

using namespace vec_math;

int main(void) {
    srand((unsigned)time(NULL));  
    for(int i = 0; i < 10; ++i) {
        std::cout << rand_vec3(-10, 10) << std::endl; 
    }
    return 0;
}
