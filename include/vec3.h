#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <math.h>

namespace vec_math {
    
    class vec3 {
    public:
        // constructors
        vec3(float x = 0, float y = 0, float z = 0);
        vec3(const vec3& other);
        vec3 &operator=(const vec3& other);

        // getter and setter
        float &x();
        const float &x() const;
        float &y();
        const float &y() const;
        float &z();
        const float &z() const;
       
        // math operations
        friend vec3 clamp_vector(const vec3 &a, const vec3 &min, const vec3 &max);
        friend vec3 clamp_vector_value(const vec3 &a, const float min, const float max);
        
        friend vec3 operator-(const vec3& a);
        friend vec3 operator+(const vec3 &a, const vec3& b);
        friend vec3 operator-(const vec3 &a, const vec3& b);
        friend vec3 operator*(const vec3 &a, const vec3& b);
        friend vec3 operator*(const vec3 &a, float s);
        friend vec3 operator*(float s, const vec3 &a);
        friend vec3 operator/(const vec3 &a, const vec3& b);
        friend vec3 operator/(const vec3 &a, float s);
   
        float length_squared() const;
        float length() const;
        friend vec3 normalize(const vec3 &a);
        friend float get_distance_squared(const vec3 &a, const vec3 &b);
        friend float get_distance(const vec3 &a, const vec3 &b);
        friend float dot(const vec3 &a, const vec3 &b);
        friend vec3 cross(const vec3 &a, const vec3 &b);

        // debug
        friend std::ostream &operator<<(std::ostream& out, const vec3& vec);

    private:
        float v[3];
    };
     
    // general math functions
    float rand_float();
    vec3 rand_vec3(const float min, const float max);
    float clamp_float(float x, float min, float max);
}

#endif // VEC3_H
