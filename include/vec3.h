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
        friend vec3 dot(const vec3 &a, const vec3 &b);
        friend vec3 cross(const vec3 &a, const vec3 &b);
        
        // debug
        friend std::ostream& operator<<(std::ostream& out, const vec3& vec);

    private:
        float v[3];
    };

}

#endif // VEC3_H
