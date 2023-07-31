#include <iostream>
#include <thread>
#include "../include/mini_math.h"

using namespace mini_math;

static uint32_t seed = time(NULL);

int main(void) {
 
    vec2 a = { 1, 0 };
    vec2 b = { 0, 1 };
   
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << "lerp : "  << lerp (a, b, 0.5) << std::endl ;
    std::cout << "clamp < -1, -1 > to < 5, 6 > : " << clamp(a, vec2(-1, -1), vec2(5, 6)) << std::endl;
    std::cout << "clamp 5 to 20 : " << clamp(a, 5, 20) << std::endl;

    std::cout << "-a = " << -a    << std::endl; 
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a * 5 = " << a * 5 << std::endl;
    std::cout << "10 * b = " << 10 * b << std::endl;
    std::cout << "a / b  = " << a / b << std::endl; 
    std::cout << "a / 10 = " << a / 10 << std::endl; 
   
    std::cout << "length a : " << a.length() << std::endl;
    std::cout << "a cross b : " << cross(a, b) << std::endl;

    return 0;
}
