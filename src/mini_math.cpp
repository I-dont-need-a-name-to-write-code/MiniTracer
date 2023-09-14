#include "../include/mini_math.h"

namespace mmath {

    // MATRIX44 
    const mat4x4 mat4x4::IDENTITY = mat4x4 (
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    const mat4x4 mat4x4::ZERO = mat4x4 ( 
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    );

    mat4x4::mat4x4() {
        this->copy(mat4x4::IDENTITY);
    }

    mat4x4::mat4x4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33) 
    {
        this->data[0][0] = m00;  this->data[0][1] = m01; this->data[0][2] = m02; this->data[0][3] = m03;
        this->data[1][0] = m10;  this->data[1][1] = m11; this->data[1][2] = m12; this->data[1][3] = m13;
        this->data[2][0] = m20;  this->data[2][1] = m21; this->data[2][2] = m22; this->data[2][3] = m23;
        this->data[3][0] = m30;  this->data[3][1] = m31; this->data[3][2] = m32; this->data[3][3] = m33;
    }

    mat4x4::mat4x4(const mat4x4 &other) {
        this->copy(other);
    }

    mat4x4 &mat4x4::operator=(const mat4x4 &other) {
        if(this != &other) {
            this->copy(other);
        }
        return *this;
    }

    float &mat4x4::at(uint8_t i, uint8_t j) { return this->data[i][j]; }
    const float &mat4x4::at(uint8_t i, uint8_t j) const { return this->data[i][j]; }
    
    void mat4x4::copy(const mat4x4 &other) {
        for(uint8_t i = 0; i < 16; ++i) {
           *((float*)&this->data + i) = *((float*)&other.data + i);
        }
    }

    vec3 operator*(const mat4x4 &m, const vec3 &v) {
        vec3 res;
        res.x() = (m.data[0][0] * v.x()) + (m.data[0][1] * v.y()) + (m.data[0][2] * v.z()) + m.data[0][3];
        res.y() = (m.data[1][0] * v.x()) + (m.data[1][1] * v.y()) + (m.data[1][2] * v.z()) + m.data[1][3];
        res.z() = (m.data[2][0] * v.x()) + (m.data[2][1] * v.y()) + (m.data[2][2] * v.z()) + m.data[2][3];
        float w = (m.data[3][0] * v.x()) + (m.data[3][1] * v.y()) + (m.data[3][2] * v.z()) + m.data[3][3];
        
        if((w != 1.0f) && (w != 0.0f) && (w != -0.0f)) {
            float inv_w = 1.0f / w;
            res.x() *= inv_w;
            res.y() *= inv_w;
            res.z() *= inv_w;
        }

        return res;
    }

    mat4x4 operator+(const mat4x4 &a, const mat4x4 &b) {
        mat4x4 c;
        for(uint8_t i = 0; i < 4; ++i) {
            for(uint8_t j = 0; j < 4; ++j) { 
                c.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return c;
    }

    mat4x4 operator-(const mat4x4 &a, const mat4x4 &b) {
        mat4x4 c;
        for(uint8_t i = 0; i < 4; ++i) {
            for(uint8_t j = 0; j < 4; ++j) { 
                c.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return c;
    }

    mat4x4 operator*(const mat4x4 &a, const mat4x4 &b) {
        mat4x4 c;
        for(uint8_t i = 0; i < 4; ++i) {
            for(uint8_t j = 0; j < 4; ++j) { 
                c.data[i][j] = 0;
                for(uint8_t k = 0; k < 4; ++k) {
                    c.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return c;
    }

    mat4x4 operator*(const mat4x4 &a, const float scaler) {
        mat4x4 res;
        for(uint8_t i = 0; i < 4; ++i) {
            for(uint8_t j = 0; j < 4; ++j) {
                res.data[i][j] = scaler * a.data[i][j];
            }
        }
        return res;
    }

    mat4x4 operator*(const float scaler, const mat4x4 &a) {
        return (a * scaler);
    }

    mat4x4 mat4x4::rotateX(const float angle) {
        const float a = sinf(angle);
        const float b = cosf(angle);
        mat4x4 res = mat4x4 (
            1.0f,  0.0f, 0.0f, 0.0f,
            0.0f,  b   , a   , 0.0f,
            0.0f, -a   , b   , 0.0f,
            0.0f,  0.0f, 0.0f, 1.0f
        );
        return res;
    }

    mat4x4 mat4x4::rotateY(const float angle) {
        (void)angle;
        return mat4x4::ZERO;
    }

    mat4x4 mat4x4::rotateZ(const float angle) {
        (void)angle;
        return mat4x4::ZERO;
    }

    mat4x4 &mat4x4::transpose() {
        float temp;
        for(uint8_t d = 0; d < 3; ++d) {
            for(uint8_t i = (d + 1); i < 4; ++i) {
                temp = this->data[d][i];
                this->data[d][i] = this->data[i][d];
                this->data[i][d] = temp;
            }
        }
        return *this;
    }

    mat4x4 mat4x4::transpose(const mat4x4 &a) {
        mat4x4 a_t;
        for(uint8_t i = 0; i < 4; ++i) {
            for(uint8_t j = 0; j < 4; ++j) {
                a_t.data[j][i] = a.data[i][j];   
            }
        }
        return a_t;
    }

    float mat4x4::determinant(const mat4x4 &a) {
        float s0 = a.data[0][0] * a.data[1][1] - a.data[1][0] * a.data[0][1];
        float s1 = a.data[0][0] * a.data[1][2] - a.data[1][0] * a.data[0][2];
        float s2 = a.data[0][0] * a.data[1][3] - a.data[1][0] * a.data[0][3];
        float s3 = a.data[0][1] * a.data[1][2] - a.data[1][1] * a.data[0][2];
        float s4 = a.data[0][1] * a.data[1][3] - a.data[1][1] * a.data[0][3];
        float s5 = a.data[0][2] * a.data[1][3] - a.data[1][2] * a.data[0][3];

        float c5 = a.data[2][2] * a.data[3][3] - a.data[3][2] * a.data[2][3];
        float c4 = a.data[2][1] * a.data[3][3] - a.data[3][1] * a.data[2][3];
        float c3 = a.data[2][1] * a.data[3][2] - a.data[3][1] * a.data[2][2];
        float c2 = a.data[2][0] * a.data[3][3] - a.data[3][0] * a.data[2][3];
        float c1 = a.data[2][0] * a.data[3][2] - a.data[3][0] * a.data[2][2];
        float c0 = a.data[2][0] * a.data[3][1] - a.data[3][0] * a.data[2][1];
    
        return (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
    }

    optional<mat4x4> mat4x4::inverse(const mat4x4 &a) {
        optional<mat4x4> r;
        float s0 = a.data[0][0] * a.data[1][1] - a.data[1][0] * a.data[0][1];
        float s1 = a.data[0][0] * a.data[1][2] - a.data[1][0] * a.data[0][2];
        float s2 = a.data[0][0] * a.data[1][3] - a.data[1][0] * a.data[0][3];
        float s3 = a.data[0][1] * a.data[1][2] - a.data[1][1] * a.data[0][2];
        float s4 = a.data[0][1] * a.data[1][3] - a.data[1][1] * a.data[0][3];
        float s5 = a.data[0][2] * a.data[1][3] - a.data[1][2] * a.data[0][3];

        float c5 = a.data[2][2] * a.data[3][3] - a.data[3][2] * a.data[2][3];
        float c4 = a.data[2][1] * a.data[3][3] - a.data[3][1] * a.data[2][3];
        float c3 = a.data[2][1] * a.data[3][2] - a.data[3][1] * a.data[2][2];
        float c2 = a.data[2][0] * a.data[3][3] - a.data[3][0] * a.data[2][3];
        float c1 = a.data[2][0] * a.data[3][2] - a.data[3][0] * a.data[2][2];
        float c0 = a.data[2][0] * a.data[3][1] - a.data[3][0] * a.data[2][1];

        float d = (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
        if(d == 0.0f) {
            r.type = result_type::NONE;
            return r;
        }

        mat4x4 &m = r.result;
        float inv_d = 1.0f / d;      

        m.data[0][0] = ( a.data[1][1] * c5 - a.data[1][2] * c4 + a.data[1][3] * c3) * inv_d;
        m.data[0][1] = (-a.data[0][1] * c5 + a.data[0][2] * c4 - a.data[0][3] * c3) * inv_d;
        m.data[0][2] = ( a.data[3][1] * s5 - a.data[3][2] * s4 + a.data[3][3] * s3) * inv_d;
        m.data[0][3] = (-a.data[2][1] * s5 + a.data[2][2] * s4 - a.data[2][3] * s3) * inv_d;
                                                                       
        m.data[1][0] = (-a.data[1][0] * c5 + a.data[1][2] * c2 - a.data[1][3] * c1) * inv_d;
        m.data[1][1] = ( a.data[0][0] * c5 - a.data[0][2] * c2 + a.data[0][3] * c1) * inv_d;
        m.data[1][2] = (-a.data[3][0] * s5 + a.data[3][2] * s2 - a.data[3][3] * s1) * inv_d;
        m.data[1][3] = ( a.data[2][0] * s5 - a.data[2][2] * s2 + a.data[2][3] * s1) * inv_d;
                                                                       
        m.data[2][0] = ( a.data[1][0] * c4 - a.data[1][1] * c2 + a.data[1][3] * c0) * inv_d;
        m.data[2][1] = (-a.data[0][0] * c4 + a.data[0][1] * c2 - a.data[0][3] * c0) * inv_d;
        m.data[2][2] = ( a.data[3][0] * s4 - a.data[3][1] * s2 + a.data[3][3] * s0) * inv_d;
        m.data[2][3] = (-a.data[2][0] * s4 + a.data[2][1] * s2 - a.data[2][3] * s0) * inv_d;
                                                                       
        m.data[3][0] = (-a.data[1][0] * c3 + a.data[1][1] * c1 - a.data[1][2] * c0) * inv_d;
        m.data[3][1] = ( a.data[0][0] * c3 - a.data[0][1] * c1 + a.data[0][2] * c0) * inv_d;
        m.data[3][2] = (-a.data[3][0] * s3 + a.data[3][1] * s1 - a.data[3][2] * s0) * inv_d;
        m.data[3][3] = ( a.data[2][0] * s3 - a.data[2][1] * s1 + a.data[2][2] * s0) * inv_d;

        r.type = result_type::SOME;
        return r; 
    }

    std::ostream &operator<<(std::ostream &out, const mat4x4 &other) {
        out << "(_DEBUG_) MATRIX4x4 -> [\n";
        for(uint8_t i = 0; i < 4; ++i) {
            out << "  [";
            for(uint8_t j = 0; j < 4; ++j) {
                out << other.data[i][j];
                if(j != 3) out << ", ";
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
    
    vec2 vec2::lerp(const vec2 &a, const vec2 &b, const float t) {
        return (a + (b - a) * t);
    }

    vec2 vec2::clamp(const vec2 &a, const vec2 &min, const vec2 &max) {
        return vec2( clampf(a.v[0], min.v[0], max.v[0]),
                     clampf(a.v[1], min.v[1], max.v[1]) );
    }

    vec2 vec2::clamp(const vec2 &a, const float min, const float max) {        
        return vec2( clampf(a.v[0], min, max),
                     clampf(a.v[1], min, max) );
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

    vec2 vec2::normalize(const vec2 &a) {
        return (a / a.length());
    }

    float vec2::get_distance_squared(const vec2 &a, const vec2 &b) {
        return (b - a).length_squared();
    }

    float vec2::get_distance(const vec2 &a, const vec2 &b) {
        return M_SQRT(get_distance_squared(a, b));
    }

    float vec2::dot(const vec2 &a, const vec2 &b) {
        return ( (a.v[0] * b.v[0]) +
                 (a.v[1] * b.v[1]) );
    }

    float vec2::cross(const vec2 &a, const vec2 &b) {
        return ( (a.v[0] * b.v[1]) - 
                 (a.v[1] * b.v[0]) );
    }

    float vec2::angle_between(const vec2 &a, const vec2 &b) {
        return acosf(dot(a, b) / M_SQRT(a.length_squared() * b.length_squared()));
    }

    vec2 vec2::reflect(const vec2 &incident_ray, const vec2 &normal) {
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

    vec3 vec3::lerp(const vec3 &a, const vec3 &b, const float t) {
        return (a + (b - a) * t);
    }

    vec3 vec3::clamp(const vec3 &a, const vec3 &min, const vec3 &max) {
        return vec3( clampf(a.v[0], min.v[0], max.v[0]),
                     clampf(a.v[1], min.v[1], max.v[1]), 
                     clampf(a.v[2], min.v[2], max.v[2]) );
    }

    vec3 vec3::clamp(const vec3 &a, const float min, const float max) {
        return vec3( clampf(a.v[0], min, max),
                     clampf(a.v[1], min, max), 
                     clampf(a.v[2], min, max) );
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

    vec3 vec3::normalize(const vec3 &a) {
        return (a / a.length());
    }

    float vec3::get_distance_squared(const vec3 &a, const vec3 &b) {
        return (b - a).length_squared();
    }

    float vec3::get_distance(const vec3 &a, const vec3 &b) {
        return M_SQRT(get_distance_squared(a, b));
    }
    
    float vec3::dot(const vec3 &a, const vec3 &b) {
        return ( (a.v[0] * b.v[0]) +
                 (a.v[1] * b.v[1]) +
                 (a.v[2] * b.v[2]) );
    }

    vec3 vec3::cross(const vec3 &a, const vec3 &b) {
        return vec3( (a.v[1] * b.v[2] - a.v[2] * b.v[1]),
                     (a.v[2] * b.v[0] - a.v[0] * b.v[2]),
                     (a.v[0] * b.v[1] - a.v[1] * b.v[0]) );
    }

    float vec3::angle_between(const vec3 &a, const vec3 &b) {
        return acosf(dot(a, b) / M_SQRT(a.length_squared() * b.length_squared()));
    }

    vec3 vec3::reflect(const vec3 &incident_ray, const vec3 &normal) {
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
    
    float lerpf(const float a, const float b, const float t) {
        return (a + (b - a) * t);
    }

    float clampf(const float x, const float min, const float max) {
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
        if(vec2::dot(r, normal) < 0.0f) return -r;
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
        if(vec3::dot(normal, r) < 0.0f) return -r;
        return r;
    }

}
