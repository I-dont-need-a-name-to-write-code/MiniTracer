#include "../include/mobject.h"

Sphere::Sphere(const point3 &origin, const float radius) {
    this->radius = radius;
    this->origin = origin;
}

float  &Sphere::r() { return this->radius; }
point3 &Sphere::o() { return this->origin; }

const float  &Sphere::r() const { return this->radius; }
const point3 &Sphere::o() const { return this->origin; }

Hit_Info Sphere::hit(const Sphere &sphere, const ray &r) {
    Hit_Info info;
    vec3 sr = r.o() - sphere.o();
    float a = vec3::dot(r.d(), r.d());
    float b = 2 * vec3::dot(r.d(), sr);
    float c = vec3::dot(sr, sr) - sphere.r() * sphere.r();
    
    float d = b * b - 4 * a * c;
    if(d < 0.0f) {
        info.is_hit = false;
        return info;
    }

    float sqrt_d = sqrtf(d);
    float t = (-b - sqrt_d) / (2 * a);
    if(t < 0.001f) {
        t = (-b + sqrt_d) / (2 * a);
        if(t < 0.001f) {
            info.is_hit = false;
            return info;
        }
    }

    info.is_hit = true;
    info.t = t;

    return info;
}
