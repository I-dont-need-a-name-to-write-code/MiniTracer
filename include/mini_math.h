#ifndef MINI_MATH_H
#define MINI_MATH_H

#include <iostream>
#include <math.h>
#include <limits>

#ifndef M_PI
    #define M_PI 3.14159265358979323846f
#endif

namespace mini_math {

    class vec3 {
    public:
        // constructors
        vec3(float x = 0.f, float y = 0.f, float z = 0.f);
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
        friend float angle_between(const vec3 &a, const vec3 &b);
        friend vec3 reflect(const vec3 &incident_ray, const vec3 &normal);

        // debug
        friend std::ostream &operator<<(std::ostream& out, const vec3& vec);

    private:
        float v[3];
    };

    using color3 = vec3;
    using point3 = vec3;
    using float3 = vec3;

    class ray {
        public: 
            ray(const vec3 &orig, const vec3 &dir);
            ray(const ray &other);
            ray &operator=(const ray &other);

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
    vec3 random_vec3(uint32_t &seed, const float min = -1.0f, const float max = 1.0f);
    vec3 random_in_unit_sphere(uint32_t &seed);
    vec3 random_in_unit_hemisphere(uint32_t &seed, const vec3 &normal);

}

#endif // MINI_MATH_H
