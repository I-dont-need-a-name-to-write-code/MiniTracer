#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
 
    matrix44 a (
        1, 1, 1, -1,
        1, 1, -1, 1,
        1, -1, 1, 1,
        -1, 1, 1, 1
    );

    matrix44 b ( 
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    );

    optional<matrix44> inv_a = inverse(a);
    if(inv_a.type == SOME) {
        std::cout << inv_a.result << std::endl; 
    } else {
        std::cout << "NONE!\n";
    }
    
    optional<matrix44> inv_b = inverse(b);
    if(inv_b.type == SOME) {
        std::cout << inv_b.result << std::endl; 
    } else {
        std::cout << "NONE!\n";
    }

    return 0;
}
