#include "../include/mobject.h"

Object::Object(Object_Type type, void *p_obj) {
    this->type  = type;
    this->p_obj = p_obj;
}

Sphere::Sphere(const point3 &origin, const float radius, const Material *p_mat) {
    this->radius = radius;
    this->origin = origin;
    this->p_material = p_mat;
}

float  &Sphere::r() { return this->radius; }
point3 &Sphere::o() { return this->origin; }

const float  &Sphere::r() const { return this->radius; }
const point3 &Sphere::o() const { return this->origin; }

const Material *Sphere::p_mat() const {
    return this->p_material;
}

Hit_Info Sphere::hit(const Sphere &sphere, const ray &r) {
   
    vec3 sr = r.o() - sphere.o();
    float a = vec3::dot(r.d(), r.d());
    float b = 2 * vec3::dot(r.d(), sr);
    float c = vec3::dot(sr, sr) - sphere.r() * sphere.r();
    
    Hit_Info info;

    float d = b * b - 4 * a * c;
    if(d < 0.0f) {
        info.is_hit = false;
        return info;
    }

    float sqrt_d = sqrtf(d);
    float t = (-b - sqrt_d) / (2 * a);
    if(t < 0.0f) {
        t = (-b + sqrt_d) / (2 * a);
        if(t < 0.0f) {
            info.is_hit = false;
            return info;
        }
    }

    info.is_hit = true;
    info.t = t;
    info.hit_point = r.at(t);
    info.normal = (info.hit_point - sphere.o()) / sphere.r();
    info.p_mat = sphere.p_mat();

    return info;
}