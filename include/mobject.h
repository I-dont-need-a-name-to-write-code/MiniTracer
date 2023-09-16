#ifndef MINI_OBJECT_H
#define MINI_OBJECT_H

#include "./mmath.h"

class Hit_Info;

enum class Object_Type {
    DEFAULT,
    SPHERE
};

struct Object {
    void *p_obj = nullptr;
    Object_Type type = Object_Type::DEFAULT;
};

class Sphere {
public:
    Sphere(const point3 &origin, const float radius);
    static Hit_Info hit(const Sphere &sphere, const ray &r);
private:
    float  r;
    point3 o;
};  

#endif // MINI_OBJECT_H


