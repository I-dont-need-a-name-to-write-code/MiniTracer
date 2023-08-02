#include "../include/mini_math.h"

namespace mini_math {

    // MATRIX_4x4
    matrix_4x4::matrix_4x4(float16 data) {
        for(int i = 0; i < 16; ++i) {
            this->data.v[i] = data.v[i];
        }
    }

    matrix_4x4::matrix_4x4(const matrix_4x4 &other) {
        for(int i = 0; i < 16; ++i) {
            this->data.v[i] = other.data.v[i];
        }
    }

    matrix_4x4 &matrix_4x4::operator=(const matrix_4x4 &other) {
        if(this != &other) {            
            for(int i = 0; i < 16; ++i) {
                this->data.v[i] = other.data.v[i];
            }
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &out, const matrix_4x4 &matrix) {
        out << "MATRIX_4X4 (DEBUG) : [\n";
        for(int i = 0; i < 4; ++i) {
            out << "[";
            for(int j = 0; j < 4; ++j) {
                out << matrix.data.v[i * 4 + j];
                if(j != 3) std::cout << ", ";
            }
            out << "]\n";
        }
        out << "]";
        return out;
    }

    // VEC2
    vec2::vec2(float x, float y) {
        this->v[0] = x;
        this->v[1] = y;
    }

    vec2::vec2(const vec2& other) {
        this->v[0] = other.v[0];
        this->v[1] = other.v[1];
    }

    vec2 &vec2::operator=(const vec2& other) {
        if(this != &other) {
            this->v[0] = other.v[0];
            this->v[1] = other.v[1];
        } 
        return *this;
    }
    
    float &vec2::x() { return this->v[0]; }
    float &vec2::y() { return this->v[1]; }
    
    const float &vec2::x() const { return this->v[0]; }
    const float &vec2::y() const { return this->v[1]; }
    
    vec2 lerp(const vec2 &a, const vec2 &b, const float t) {
        return (a + (b - a) * t);
    }

    vec2 clamp(const vec2 &a, const vec2 &min, const vec2 &max) {
        return vec2( clamp(a.v[0], min.v[0], max.v[0]),
                     clamp(a.v[1], min.v[1], max.v[1]) );
    }

    vec2 clamp(const vec2 &a, const float min, const float max) {        
        return vec2( clamp(a.v[0], min, max),
                     clamp(a.v[1], min, max) );
    }
    
    vec2 operator-(const vec2 &a) {
        return vec2(-a.v[0], -a.v[1]);   
    }

    vec2 operator+(const vec2 &a, const vec2& b) {
        return vec2( (a.v[0] + b.v[0]),
                     (a.v[1] + b.v[1]) );   
    }

    vec2 operator-(const vec2 &a, const vec2& b) {
        return vec2( (a.v[0] - b.v[0]),
                     (a.v[1] - b.v[1]) );   
    }

    vec2 operator*(const vec2 &a, const vec2& b) {
        return vec2( (a.v[0] * b.v[0]),
                     (a.v[1] * b.v[1]) );   
    }

    vec2 operator*(const vec2 &a, float s) {  
        return vec2( (a.v[0] * s),
                     (a.v[1] * s) );   
    }

    vec2 operator*(float s, const vec2 &a) {
        return (a * s);  
    }

    vec2 operator/(const vec2 &a, const vec2& b) {
        return vec2( (a.v[0] / b.v[0]),
                     (a.v[1] / b.v[1]) );   
    }

    vec2 operator/(const vec2 &a, float s) {
        return (a * (1.0f / s));
    }
    
    float vec2::length_squared() const {
        return ( (this->v[0] * this->v[0]) +
                 (this->v[1] * this->v[1]) );
    }

    float vec2::length() const {
        return M_SQRT(this->length_squared());
    }

    vec2 normalize(const vec2 &a) {
        return (a / a.length());
    }

    float get_distance_squared(const vec2 &a, const vec2 &b) {
        return (b - a).length_squared();
    }

    float get_distance(const vec2 &a, const vec2 &b) {
        return M_SQRT(get_distance_squared(a, b));
    }

    float dot(const vec2 &a, const vec2 &b) {
        return ( (a.v[0] * b.v[0]) +
                 (a.v[1] * b.v[1]) );
    }

    float cross(const vec2 &a, const vec2 &b) {
        return ( (a.v[0] * b.v[1]) - 
                 (a.v[1] * b.v[0]) );
    }

    float angle_between(const vec2 &a, const vec2 &b) {
        return acosf(dot(a, b) / M_SQRT(a.length_squared() * b.length_squared()));
    }

    vec2 reflect(const vec2 &incident_ray, const vec2 &normal) {
        return incident_ray - (2 * dot(incident_ray, normal) * normal);
    }
    
    std::ostream &operator<<(std::ostream& out, const vec2& vec) {
        out << "[" << vec.v[0] << ", " << vec.v[1] << "]";
        return out;
    }

    // VEC3
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

    vec3 operator-(const vec3 &a) {
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
        return (a * (1.0f / s));
    }

    float vec3::length_squared() const {
        return ( (this->v[0] * this->v[0]) + 
                 (this->v[1] * this->v[1]) +
                 (this->v[2] * this->v[2]) );
    }
    
    float vec3::length() const {
        return M_SQRT(this->length_squared());
    }

    vec3 normalize(const vec3 &a) {
        return (a / a.length());
    }

    float get_distance_squared(const vec3 &a, const vec3 &b) {
        return (b - a).length_squared();
    }

    float get_distance(const vec3 &a, const vec3 &b) {
        return M_SQRT(get_distance_squared(a, b));
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
        return acosf(dot(a, b) / M_SQRT(a.length_squared() * b.length_squared()));
    }

    vec3 reflect(const vec3 &incident_ray, const vec3 &normal) {
        return incident_ray - (2 * dot(incident_ray, normal) * normal);
    }

    std::ostream &operator<<(std::ostream& out, const vec3& vec) {
        out << "[" << vec.v[0] << ", " << vec.v[1] << ", " << vec.v[2] << "]";
        return out;
    }

    // RAY
    ray::ray(const vec3 &orig, const vec3 &dir) {
        this->origin = orig;
        this->direction = dir;
    }

    ray::ray(const ray &other) {
        this->origin = other.origin;
        this->direction = other.direction;
    }

    ray &ray::operator=(const ray &other) {
        if(this != &other) {
            this->origin = other.origin;
            this->direction = other.direction;
        }
        return *this;
    }

    vec3 &ray::orig() { return this->origin; }
    vec3 &ray::dir() { return this->direction; }

    const vec3 &ray::orig() const { return this->origin; }
    const vec3 &ray::dir() const { return this->direction; }
    
    vec3 ray::at(const float t) { 
        return (this->origin + (this->direction * t)); 
    }

    // general math functions
    
    float lerp(const float a, const float b, const float t) {
        return (a + (b - a) * t);
    }

    float clamp(const float x, const float min, const float max) {
        if(x < min) return min;
        if(x > max) return max;
        return x;
    }

    float rad_to_deg(const float radians) {
        return radians * (180 / M_PI);
    }

    float deg_to_rad(const float degrees) {
        return degrees * (M_PI / 180);
    }

    uint32_t pcg_hash(uint32_t input) {
        uint32_t state = input * 747796405u + 2891336453u;
        uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }
    
    float random_float(uint32_t &seed) {
        seed = pcg_hash(seed);
        constexpr uint32_t UINT32_T_MAX = std::numeric_limits<uint32_t>::max();
        return ((float)seed / (float)UINT32_T_MAX);  
    }

    vec2 random_vec2(uint32_t &seed, const float min, const float max) {        
        float range = (max - min);
        return vec2( (min + random_float(seed) * range),
                     (min + random_float(seed) * range) );
    }

    vec2 random_in_unit_circle(uint32_t &seed) {
        vec2 r;
        do {
            r = random_vec2(seed, -1.0f, 1.0f);
        } while(r.length_squared() > 1.0f);
        return r;
    }

    vec2 random_in_unit_semicircle(uint32_t &seed, const vec2 &normal) {
        vec2 r = random_in_unit_circle(seed);
        if(dot(r, normal) < 0.0f) return -r;
        return r;
    }

    vec3 random_vec3(uint32_t &seed, const float min, const float max) { 
        float range = (max - min);
        return vec3( (min + random_float(seed) * range),
                     (min + random_float(seed) * range), 
                     (min + random_float(seed) * range) );
    }

    vec3 random_in_unit_sphere(uint32_t &seed) {
        vec3 r;
        do {
            r = random_vec3(seed, -1.0f, 1.0f);
        } while(r.length_squared() > 1.0f);
        return r;
    }

    vec3 random_in_unit_hemisphere(uint32_t &seed, const vec3 &normal) {
        vec3 r = random_in_unit_sphere(seed);
        if(dot(normal, r) < 0.0f) return -r;
        return r;
    }

}
