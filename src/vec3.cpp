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
    
    vec3 dot(const vec3 &a, const vec3 &b) {
        return vec3();
    }

    vec3 cross(const vec3 &a, const vec3 &b) {
        return vec3();
    }

    std::ostream& operator<<(std::ostream& out, const vec3& vec) {
        out << "[" << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << "]";
        return out;
    }

}
