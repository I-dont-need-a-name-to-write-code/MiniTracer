#include "../include/vec3.h"

namespace vec_math {

    vec3::vec3(float x, float y, float z) {
        this->v[0] = x; 
        this->v[1] = y;
        this->v[2] = z;
    }

    vec3::vec3(const vec3& other) {
        this->v[0] = other.v[0]; 
        this->v[1] = other.v[1];
        this->v[2] = other.v[2];
    }

    vec3 &vec3::operator=(const vec3& other) {
        if(this != &other) {
            this->v[0] = other.v[0];
            this->v[1] = other.v[1];
            this->v[2] = other.v[2];
        }
        return *this;
    }

    float &vec3::x() { return this->v[0]; }
    float &vec3::y() { return this->v[1]; }
    float &vec3::z() { return this->v[2]; }
    const float &vec3::x() const { return this->v[0]; } 
    const float &vec3::y() const { return this->v[1]; } 
    const float &vec3::z() const { return this->v[2]; }     

    vec3 lerp(const vec3 &a, const vec3 &b, const float t) {
        return (a + (b - a) * t);
    }

    vec3 clamp(const vec3 &a, const vec3 &min, const vec3 &max) {
        return vec3( clamp(a.v[0], min.v[0], max.v[0]),
                     clamp(a.v[1], min.v[1], max.v[1]), 
                     clamp(a.v[2], min.v[2], max.v[2]) );
    }

    vec3 clamp(const vec3 &a, const float min, const float max) {
        return vec3( clamp(a.v[0], min, max),
                     clamp(a.v[1], min, max), 
                     clamp(a.v[2], min, max) );
    }

    vec3 operator-(const vec3& a) {
        return vec3(-a.v[0], -a.v[1], -a.v[2]);
    }

    vec3 operator+(const vec3 &a, const vec3& b) {
        return vec3( (a.v[0] + b.v[0]), 
                     (a.v[1] + b.v[1]),
                     (a.v[2] + b.v[2]) );
    }

    vec3 operator-(const vec3 &a, const vec3& b) {
        return vec3( (a.v[0] - b.v[0]), 
                     (a.v[1] - b.v[1]),
                     (a.v[2] - b.v[2]) );
    }

    vec3 operator*(const vec3 &a, const vec3& b) {
        return vec3( (a.v[0] * b.v[0]), 
                     (a.v[1] * b.v[1]),
                     (a.v[2] * b.v[2]) );
    }

    vec3 operator*(const vec3 &a, float s) {
        return vec3( (a.v[0] * s), 
                     (a.v[1] * s),
                     (a.v[2] * s) );
    }

    vec3 operator*(float s, const vec3 &a) {
        return (a * s);
    }

    vec3 operator/(const vec3 &a, const vec3& b) {
        return vec3( (a.v[0] / b.v[0]), 
                     (a.v[1] / b.v[1]),
                     (a.v[2] / b.v[2]) );
    }

    vec3 operator/(const vec3 &a, float s) {
        return (a * (1 / s));
    }

    float vec3::length_squared() const {
        return ( (this->v[0] * this->v[0]) + 
                 (this->v[1] * this->v[1]) +
                 (this->v[2] * this->v[2]) );
    }
    
    float vec3::length() const {
        return sqrtf(this->length_squared());
    }

    vec3 normalize(const vec3 &a) {
        return (a / a.length());
    }

    float get_distance_squared(const vec3 &a, const vec3 &b) {
        return (b - a).length_squared();
    }

    float get_distance(const vec3 &a, const vec3 &b) {
        return sqrtf(get_distance_squared(a, b));
    }
    
    float dot(const vec3 &a, const vec3 &b) {
        return ( (a.v[0] * b.v[0]) +
                 (a.v[1] * b.v[1]) +
                 (a.v[2] * b.v[2]) );
    }

    vec3 cross(const vec3 &a, const vec3 &b) {
        return vec3( (a.v[1] * b.v[2] - a.v[2] * b.v[1]),
                     (a.v[2] * b.v[0] - a.v[0] * b.v[2]),
                     (a.v[0] * b.v[1] - a.v[1] * b.v[0]) );
    }

    float angle_between(const vec3 &a, const vec3 &b) {
    }

    std::ostream &operator<<(std::ostream& out, const vec3& vec) {
        out << "[" << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << "]";
        return out;
    }

    // general math functions
    
    float rand_float() {
        return ((float)rand() / (float)RAND_MAX);  
    }

    vec3 rand_vec3(const float min, const float max) {        
        float range = (max - min);
        return vec3( min + rand_float() * range,
                     min + rand_float() * range, 
                     min + rand_float() * range );
    }

    float lerp(const float a, const float b, const float t) {
        return (a + (b - a) * t);
    }

    float clamp(float x, float min, float max) {
        if(x < min) return min;
        if(x > max) return max;
        return x;
    }

}
