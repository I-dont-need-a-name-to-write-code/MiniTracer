#ifndef MINI_OBJECT_H
#define MINI_OBJECT_H

#include "./mmath.h"

struct Material {
    color3 albedo;
};

struct Hit_Info {
    bool   is_hit;
    float  t;
    point3 hit_point;
    vec3   normal;
    const Material *p_mat;
};

enum class Object_Type {
    DEFAULT,
    SPHERE
};

class Object {
public:
    Object(Object_Type type, void *p_obj);
public:
    void *p_obj = nullptr;
    Object_Type type = Object_Type::DEFAULT;
};

class Sphere {
public:
    Sphere() = default;
    Sphere(const point3 &origin, const float radius, const Material *p_mat);

    // getter and setter
    float  &r(); 
    point3 &o(); 
    const float  &r() const; 
    const point3 &o() const; 

    const Material *p_mat() const;

    // ray hit intersection
    static Hit_Info hit(const Sphere &sphere, const ray &r);

private:
    float    radius;
    point3   origin;
    const Material *p_material;
};  

#endif // MINI_OBJECT_H


