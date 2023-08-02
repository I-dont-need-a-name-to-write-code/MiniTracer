#ifndef MINI_MATH_H
#define MINI_MATH_H

#include <iostream>
#include <math.h>
#include <limits>

#ifndef M_PI
    #define M_PI 3.14159265358979323846f
#endif

#ifndef M_SQRT
    #define M_SQRT sqrtf
#endif

namespace mini_math {

    class Matrix4x4 {
    public:
        Matrix4x4();
        Matrix4x4(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33);
        Matrix4x4(const Matrix4x4 &other);
        Matrix4x4 &operator=(const Matrix4x4 &other);
    
        // getter and setter
        float &get(uint8_t i, uint8_t j);
        const float &get(uint8_t i, uint8_t j) const;
       
        // debug
        friend std::ostream &operator<<(std::ostream &out, const Matrix4x4 &other);
            
    public:
        static const Matrix4x4 Identity;

    private:
        float data[4][4];

    private:
        void copy(const Matrix4x4 &other);
    };

    class vec2 {
    public:
        vec2(float x = 0.0f, float y = 0.0f);
        vec2(const vec2& other);
        vec2 &operator=(const vec2& other);
        
        // getter and setter
        float &x();
        float &y();

        const float &x() const;
        const float &y() const;

        // math operations
        friend vec2 lerp(const vec2 &a, const vec2 &b, const float t);
        friend vec2 clamp(const vec2 &a, const vec2 &min, const vec2 &max);
        friend vec2 clamp(const vec2 &a, const float min, const float max);

        friend vec2 operator-(const vec2 &a);
        friend vec2 operator+(const vec2 &a, const vec2& b);
        friend vec2 operator-(const vec2 &a, const vec2& b);
        friend vec2 operator*(const vec2 &a, const vec2& b);
        friend vec2 operator*(const vec2 &a, float s);
        friend vec2 operator*(float s, const vec2 &a);
        friend vec2 operator/(const vec2 &a, const vec2& b);
        friend vec2 operator/(const vec2 &a, float s);
   
        float length_squared() const;
        float length() const;
        friend vec2 normalize(const vec2 &a);
        friend float get_distance_squared(const vec2 &a, const vec2 &b);
        friend float get_distance(const vec2 &a, const vec2 &b);
        friend float dot(const vec2 &a, const vec2 &b);
        friend float cross(const vec2 &a, const vec2 &b);
        friend float angle_between(const vec2 &a, const vec2 &b);
        friend vec2 reflect(const vec2 &incident_ray, const vec2 &normal);

        // debug
        friend std::ostream &operator<<(std::ostream& out, const vec2& vec);

    private:
            float v[2];
    };

    using float2 = vec2;
    using point2 = vec2;

    class vec3 {
    public:
        vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        vec3(const vec3& other);
        vec3 &operator=(const vec3& other);

        // getter and setter
        float &x();
        float &y();
        float &z();

        const float &x() const;
        const float &y() const;
        const float &z() const;
       
        // math operations
        friend vec3 lerp(const vec3 &a, const vec3 &b, const float t);
        friend vec3 clamp(const vec3 &a, const vec3 &min, const vec3 &max);
        friend vec3 clamp(const vec3 &a, const float min, const float max);
        
        friend vec3 operator-(const vec3 &a);
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
        friend float angle_between(const vec3 &a, const vec3 &b);
        friend vec3 reflect(const vec3 &incident_ray, const vec3 &normal);

        // debug
        friend std::ostream &operator<<(std::ostream& out, const vec3& vec);

    private:
        float v[3];
    };

    using float3 = vec3;
    using point3 = vec3;
    using color3 = vec3;
    
    class ray {
        public: 
            ray(const vec3 &orig, const vec3 &dir);
            ray(const ray &other);
            ray &operator=(const ray &other);
            
            // getter and setter
            vec3 &orig();
            vec3 &dir();

            const vec3 &orig() const;
            const vec3 &dir() const;
    
            vec3 at(const float t);

        private:
            vec3 direction;
            vec3 origin;
    };
     
    // general math functions
    float lerp(const float a, const float b, const float t);
    float clamp(const float x, const float min, const float max);
    float rad_to_deg(const float radians);
    float deg_to_rad(const float degrees);
    uint32_t pcg_hash(uint32_t input); 
    float random_float(uint32_t &seed);

    vec2 random_vec2(uint32_t &seed, const float min = -1.0f, const float max = 1.0f);
    vec2 random_in_unit_circle(uint32_t &seed);
    vec2 random_in_unit_semicircle(uint32_t &seed, const vec2 &normal);

    vec3 random_vec3(uint32_t &seed, const float min = -1.0f, const float max = 1.0f);
    vec3 random_in_unit_sphere(uint32_t &seed);
    vec3 random_in_unit_hemisphere(uint32_t &seed, const vec3 &normal);

}

#endif // MINI_MATH_H
