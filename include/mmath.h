#ifndef MINI_MATH_H
#define MINI_MATH_H

#include <cstdint>
#include <iostream>
#include <math.h>
#include <limits>

#ifndef M_PI
    #define M_PI 3.14159265358979323846f
#endif

#ifndef M_SQRT
    #define M_SQRT sqrtf
#endif

class mat4x4;
class vec2;
class vec3;

enum class Result_Type { NONE = 0 , SOME = 1 };
template <typename T>
struct Optional {
    Result_Type type;
    T result;
};

class mat4x4 {
public:
    mat4x4();
    mat4x4(float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33);
    mat4x4(const mat4x4 &other);
    mat4x4 &operator=(const mat4x4 &other);

    // getter and setter
    float &at(uint8_t i, uint8_t j);
    const float &at(uint8_t i, uint8_t j) const;
   
    // math operations
    friend vec3   operator*(const mat4x4 &m, const vec3 &v);
    friend mat4x4 operator+(const mat4x4 &a, const mat4x4 &b);
    friend mat4x4 operator-(const mat4x4 &a, const mat4x4 &b);
    friend mat4x4 operator*(const mat4x4 &a, const mat4x4 &b);
    friend mat4x4 operator*(const mat4x4 &a, const float scaler);
    friend mat4x4 operator*(const float scaler, const mat4x4 &a);
    
    static mat4x4 rotateX(const float angle);
    static mat4x4 rotateY(const float angle);
    static mat4x4 rotateZ(const float angle);

    mat4x4 &transpose();
    static mat4x4 transpose(const mat4x4 &a); 
    static float  determinant(const mat4x4 &a);
    static Optional<mat4x4> inverse(const mat4x4 &a);

    // debug
    friend std::ostream &operator<<(std::ostream &out, const mat4x4 &other);

private:
    void copy(const mat4x4 &other);
        
public:
    static const mat4x4 IDENTITY;
    static const mat4x4 ZERO;

private:
    float m_data[4][4];
};

class vec2 {
public:
    vec2();
    vec2(float s);
    vec2(float x, float y);
    vec2(const vec2& other);
    vec2 &operator=(const vec2& other);
    
    // getter and setter
    float &x();
    float &y();

    const float &x() const;
    const float &y() const;

    // math operations
    static vec2 lerp(const vec2 &a, const vec2 &b, const float t);
    static vec2 clamp(const vec2 &a, const vec2 &min, const vec2 &max);
    static vec2 clamp(const vec2 &a, const float min, const float max);

    vec2 &operator+=(const float s);
    vec2 &operator+=(const vec2 &other);

    vec2 &operator-=(const float s);
    vec2 &operator-=(const vec2 &other);

    vec2 &operator*=(const float s);
    vec2 &operator*=(const vec2 &other);

    vec2 &operator/=(const float s);
    vec2 &operator/=(const vec2 &other);

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
    static vec2  normalize(const vec2 &a);
    static float get_distance_squared(const vec2 &a, const vec2 &b);
    static float get_distance(const vec2 &a, const vec2 &b);
    static float dot(const vec2 &a, const vec2 &b);
    static float cross(const vec2 &a, const vec2 &b);
    static float angle_between(const vec2 &a, const vec2 &b);
    static vec2  reflect(const vec2 &incident_ray, const vec2 &normal);

    // debug
    friend std::ostream &operator<<(std::ostream& out, const vec2& vec);

private:
        float m_v[2];
};

using float2 = vec2;
using point2 = vec2;

class vec3 {
public:
    vec3();
    vec3(float s);
    vec3(float x, float y, float z);
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
    static vec3 lerp(const vec3 &a, const vec3 &b, const float t);
    static vec3 clamp(const vec3 &a, const vec3 &min, const vec3 &max);
    static vec3 clamp(const vec3 &a, const float min, const float max);

    vec3 &operator+=(const float s);
    vec3 &operator+=(const vec3 &other);

    vec3 &operator-=(const float s);
    vec3 &operator-=(const vec3 &other);

    vec3 &operator*=(const float s);
    vec3 &operator*=(const vec3 &other);

    vec3 &operator/=(const float s);
    vec3 &operator/=(const vec3 &other);
    
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
    static vec3 normalize(const vec3 &a);
    static float get_distance_squared(const vec3 &a, const vec3 &b);
    static float get_distance(const vec3 &a, const vec3 &b);
    static float dot(const vec3 &a, const vec3 &b);
    static vec3 cross(const vec3 &a, const vec3 &b);
    static float angle_between(const vec3 &a, const vec3 &b);
    static vec3 reflect(const vec3 &incident_ray, const vec3 &normal); 

    // debug
    friend std::ostream &operator<<(std::ostream& out, const vec3& vec);

private:
    float m_v[3];
};

using float3 = vec3;
using point3 = vec3;
using color3 = vec3;

class ray {
    public: 
        ray() = default;
        ray(const vec3 &orig, const vec3 &dir);
        ray(const ray &other);
        ray &operator=(const ray &other);
        
        // getter and setter
        vec3 &o();
        vec3 &d();

        const vec3 &o() const;
        const vec3 &d() const;

        vec3 at(const float t) const;

    private:
        vec3 m_d;
        vec3 m_o;
};
 
// general math functions
float lerpf(const float a, const float b, const float t);
float clampf(const float x, const float min, const float max);
float rad_to_deg(const float radians);
float deg_to_rad(const float degrees);

uint32_t pcg_hash(uint32_t input); 
float randf(uint32_t &seed, float min = 0.0f, float max = 1.0f);

vec2 random_vec2(uint32_t &seed, const float min = -1.0f, const float max = 1.0f);
vec2 random_in_unit_circle(uint32_t &seed);
vec2 random_in_unit_semicircle(uint32_t &seed, const vec2 &normal);

vec3 random_vec3(uint32_t &seed, const float min = -1.0f, const float max = 1.0f);
vec3 random_in_unit_sphere(uint32_t &seed);
vec3 random_in_unit_hemisphere(uint32_t &seed, const vec3 &normal);


#endif // MINI_MATH_H
