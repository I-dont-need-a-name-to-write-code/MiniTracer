#include <iostream>
#include "../include/mini_math.h"

using namespace mini_math;

int main(void) {
    srand(time(NULL));
    float3 a{ 2, -1, 3 };
    float3 b{ 2, 0, 1 };
    std::cout << angle_between(a, b) << "\n";
    std::cout << rad_to_deg(angle_between(a, b)) << "\n";
    return 0;
}
