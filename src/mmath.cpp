#include "../include/mmath.h"

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

mat4x4::mat4x4() {}

mat4x4::mat4x4(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33) 
{
    this->m_data[0][0] = m00;  this->m_data[0][1] = m01; this->m_data[0][2] = m02; this->m_data[0][3] = m03;
    this->m_data[1][0] = m10;  this->m_data[1][1] = m11; this->m_data[1][2] = m12; this->m_data[1][3] = m13;
    this->m_data[2][0] = m20;  this->m_data[2][1] = m21; this->m_data[2][2] = m22; this->m_data[2][3] = m23;
    this->m_data[3][0] = m30;  this->m_data[3][1] = m31; this->m_data[3][2] = m32; this->m_data[3][3] = m33;
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

float &mat4x4::at(uint8_t i, uint8_t j) { return this->m_data[i][j]; }
const float &mat4x4::at(uint8_t i, uint8_t j) const { return this->m_data[i][j]; }

void mat4x4::copy(const mat4x4 &other) {
    for(uint8_t i = 0; i < 16; ++i) {
       *((float*)&this->m_data + i) = *((float*)&other.m_data + i);
    }
}

vec3 operator*(const mat4x4 &m, const vec3 &v) {
    vec3 res;
    res.x() = (m.m_data[0][0] * v.x()) + (m.m_data[0][1] * v.y()) + (m.m_data[0][2] * v.z()) + m.m_data[0][3];
    res.y() = (m.m_data[1][0] * v.x()) + (m.m_data[1][1] * v.y()) + (m.m_data[1][2] * v.z()) + m.m_data[1][3];
    res.z() = (m.m_data[2][0] * v.x()) + (m.m_data[2][1] * v.y()) + (m.m_data[2][2] * v.z()) + m.m_data[2][3];
    float w = (m.m_data[3][0] * v.x()) + (m.m_data[3][1] * v.y()) + (m.m_data[3][2] * v.z()) + m.m_data[3][3];
    
    if((w != 0.0f) && (w != 1.0f)) {
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
            c.m_data[i][j] = a.m_data[i][j] + b.m_data[i][j];
        }
    }
    return c;
}

mat4x4 operator-(const mat4x4 &a, const mat4x4 &b) {
    mat4x4 c;
    for(uint8_t i = 0; i < 4; ++i) {
        for(uint8_t j = 0; j < 4; ++j) { 
            c.m_data[i][j] = a.m_data[i][j] - b.m_data[i][j];
        }
    }
    return c;
}

mat4x4 operator*(const mat4x4 &a, const mat4x4 &b) {
    mat4x4 c;
    for(uint8_t i = 0; i < 4; ++i) {
        for(uint8_t j = 0; j < 4; ++j) { 
            c.m_data[i][j] = 0;
            for(uint8_t k = 0; k < 4; ++k) {
                c.m_data[i][j] += a.m_data[i][k] * b.m_data[k][j];
            }
        }
    }
    return c;
}

mat4x4 operator*(const mat4x4 &a, const float scaler) {
    mat4x4 res;
    for(uint8_t i = 0; i < 4; ++i) {
        for(uint8_t j = 0; j < 4; ++j) {
            res.m_data[i][j] = scaler * a.m_data[i][j];
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
    const float a = sinf(angle);
    const float b = cosf(angle);
    mat4x4 res = mat4x4 (
        b   , 0.0f, -a   , 0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        a   , 0.0f,  b   , 0.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    );
    return res;
}

mat4x4 mat4x4::rotateZ(const float angle) {
    const float a = sinf(angle);
    const float b = cosf(angle);
    mat4x4 res = mat4x4 (
         b   , a   , 0.0f, 0.0f,
        -a   , b   , 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    );
    return res;
}

mat4x4 &mat4x4::transpose() {
    float temp;
    for(uint8_t d = 0; d < 3; ++d) {
        for(uint8_t i = (d + 1); i < 4; ++i) {
            temp = this->m_data[d][i];
            this->m_data[d][i] = this->m_data[i][d];
            this->m_data[i][d] = temp;
        }
    }
    return *this;
}

mat4x4 mat4x4::transpose(const mat4x4 &a) {
    mat4x4 a_t;
    for(uint8_t i = 0; i < 4; ++i) {
        for(uint8_t j = 0; j < 4; ++j) {
            a_t.m_data[j][i] = a.m_data[i][j];   
        }
    }
    return a_t;
}

float mat4x4::determinant(const mat4x4 &a) {
    float s0 = a.m_data[0][0] * a.m_data[1][1] - a.m_data[1][0] * a.m_data[0][1];
    float s1 = a.m_data[0][0] * a.m_data[1][2] - a.m_data[1][0] * a.m_data[0][2];
    float s2 = a.m_data[0][0] * a.m_data[1][3] - a.m_data[1][0] * a.m_data[0][3];
    float s3 = a.m_data[0][1] * a.m_data[1][2] - a.m_data[1][1] * a.m_data[0][2];
    float s4 = a.m_data[0][1] * a.m_data[1][3] - a.m_data[1][1] * a.m_data[0][3];
    float s5 = a.m_data[0][2] * a.m_data[1][3] - a.m_data[1][2] * a.m_data[0][3];

    float c5 = a.m_data[2][2] * a.m_data[3][3] - a.m_data[3][2] * a.m_data[2][3];
    float c4 = a.m_data[2][1] * a.m_data[3][3] - a.m_data[3][1] * a.m_data[2][3];
    float c3 = a.m_data[2][1] * a.m_data[3][2] - a.m_data[3][1] * a.m_data[2][2];
    float c2 = a.m_data[2][0] * a.m_data[3][3] - a.m_data[3][0] * a.m_data[2][3];
    float c1 = a.m_data[2][0] * a.m_data[3][2] - a.m_data[3][0] * a.m_data[2][2];
    float c0 = a.m_data[2][0] * a.m_data[3][1] - a.m_data[3][0] * a.m_data[2][1];

    return (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
}

Optional<mat4x4> mat4x4::inverse(const mat4x4 &a) {
    Optional<mat4x4> r;
    float s0 = a.m_data[0][0] * a.m_data[1][1] - a.m_data[1][0] * a.m_data[0][1];
    float s1 = a.m_data[0][0] * a.m_data[1][2] - a.m_data[1][0] * a.m_data[0][2];
    float s2 = a.m_data[0][0] * a.m_data[1][3] - a.m_data[1][0] * a.m_data[0][3];
    float s3 = a.m_data[0][1] * a.m_data[1][2] - a.m_data[1][1] * a.m_data[0][2];
    float s4 = a.m_data[0][1] * a.m_data[1][3] - a.m_data[1][1] * a.m_data[0][3];
    float s5 = a.m_data[0][2] * a.m_data[1][3] - a.m_data[1][2] * a.m_data[0][3];

    float c5 = a.m_data[2][2] * a.m_data[3][3] - a.m_data[3][2] * a.m_data[2][3];
    float c4 = a.m_data[2][1] * a.m_data[3][3] - a.m_data[3][1] * a.m_data[2][3];
    float c3 = a.m_data[2][1] * a.m_data[3][2] - a.m_data[3][1] * a.m_data[2][2];
    float c2 = a.m_data[2][0] * a.m_data[3][3] - a.m_data[3][0] * a.m_data[2][3];
    float c1 = a.m_data[2][0] * a.m_data[3][2] - a.m_data[3][0] * a.m_data[2][2];
    float c0 = a.m_data[2][0] * a.m_data[3][1] - a.m_data[3][0] * a.m_data[2][1];

    float d = (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
    if(d == 0.0f) {
        r.type = Result_Type::NONE;
        return r;
    }

    mat4x4 &m = r.result;
    float inv_d = 1.0f / d;      

    m.m_data[0][0] = ( a.m_data[1][1] * c5 - a.m_data[1][2] * c4 + a.m_data[1][3] * c3) * inv_d;
    m.m_data[0][1] = (-a.m_data[0][1] * c5 + a.m_data[0][2] * c4 - a.m_data[0][3] * c3) * inv_d;
    m.m_data[0][2] = ( a.m_data[3][1] * s5 - a.m_data[3][2] * s4 + a.m_data[3][3] * s3) * inv_d;
    m.m_data[0][3] = (-a.m_data[2][1] * s5 + a.m_data[2][2] * s4 - a.m_data[2][3] * s3) * inv_d;
                                                                   
    m.m_data[1][0] = (-a.m_data[1][0] * c5 + a.m_data[1][2] * c2 - a.m_data[1][3] * c1) * inv_d;
    m.m_data[1][1] = ( a.m_data[0][0] * c5 - a.m_data[0][2] * c2 + a.m_data[0][3] * c1) * inv_d;
    m.m_data[1][2] = (-a.m_data[3][0] * s5 + a.m_data[3][2] * s2 - a.m_data[3][3] * s1) * inv_d;
    m.m_data[1][3] = ( a.m_data[2][0] * s5 - a.m_data[2][2] * s2 + a.m_data[2][3] * s1) * inv_d;
                                                                   
    m.m_data[2][0] = ( a.m_data[1][0] * c4 - a.m_data[1][1] * c2 + a.m_data[1][3] * c0) * inv_d;
    m.m_data[2][1] = (-a.m_data[0][0] * c4 + a.m_data[0][1] * c2 - a.m_data[0][3] * c0) * inv_d;
    m.m_data[2][2] = ( a.m_data[3][0] * s4 - a.m_data[3][1] * s2 + a.m_data[3][3] * s0) * inv_d;
    m.m_data[2][3] = (-a.m_data[2][0] * s4 + a.m_data[2][1] * s2 - a.m_data[2][3] * s0) * inv_d;
                                                                   
    m.m_data[3][0] = (-a.m_data[1][0] * c3 + a.m_data[1][1] * c1 - a.m_data[1][2] * c0) * inv_d;
    m.m_data[3][1] = ( a.m_data[0][0] * c3 - a.m_data[0][1] * c1 + a.m_data[0][2] * c0) * inv_d;
    m.m_data[3][2] = (-a.m_data[3][0] * s3 + a.m_data[3][1] * s1 - a.m_data[3][2] * s0) * inv_d;
    m.m_data[3][3] = ( a.m_data[2][0] * s3 - a.m_data[2][1] * s1 + a.m_data[2][2] * s0) * inv_d;

    r.type = Result_Type::SOME;
    return r; 
}

std::ostream &operator<<(std::ostream &out, const mat4x4 &other) {
    out << "(_DEBUG_) MATRIX4x4 -> [\n";
    for(uint8_t i = 0; i < 4; ++i) {
        out << "  [";
        for(uint8_t j = 0; j < 4; ++j) {
            out << other.m_data[i][j];
            if(j != 3) out << ", ";
        }
        out << "]\n";
    }
    out << "]";
    return out;
}

// VEC2
vec2::vec2(float s) {
    this->m_v[0] = this->m_v[1] = s;
}

vec2::vec2(float x, float y) {
    this->m_v[0] = x;
    this->m_v[1] = y;
}

vec2::vec2(const vec2& other) {
    this->m_v[0] = other.m_v[0];
    this->m_v[1] = other.m_v[1];
}

vec2 &vec2::operator=(const vec2& other) {
    if(this != &other) {
        this->m_v[0] = other.m_v[0];
        this->m_v[1] = other.m_v[1];
    } 
    return *this;
}

float &vec2::x() { return this->m_v[0]; }
float &vec2::y() { return this->m_v[1]; }

const float &vec2::x() const { return this->m_v[0]; }
const float &vec2::y() const { return this->m_v[1]; }

vec2 vec2::lerp(const vec2 &a, const vec2 &b, const float t) {
    return (a + (b - a) * t);
}

vec2 vec2::clamp(const vec2 &a, const vec2 &min, const vec2 &max) {
    return vec2( clampf(a.m_v[0], min.m_v[0], max.m_v[0]),
                 clampf(a.m_v[1], min.m_v[1], max.m_v[1]) );
}

vec2 vec2::clamp(const vec2 &a, const float min, const float max) {        
    return vec2( clampf(a.m_v[0], min, max),
                 clampf(a.m_v[1], min, max) );
}

vec2 operator-(const vec2 &a) {
    return vec2(-a.m_v[0], -a.m_v[1]);   
}

vec2 operator+(const vec2 &a, const vec2& b) {
    return vec2( (a.m_v[0] + b.m_v[0]),
                 (a.m_v[1] + b.m_v[1]) );   
}

vec2 operator-(const vec2 &a, const vec2& b) {
    return vec2( (a.m_v[0] - b.m_v[0]),
                 (a.m_v[1] - b.m_v[1]) );   
}

vec2 operator*(const vec2 &a, const vec2& b) {
    return vec2( (a.m_v[0] * b.m_v[0]),
                 (a.m_v[1] * b.m_v[1]) );   
}

vec2 operator*(const vec2 &a, float s) {  
    return vec2( (a.m_v[0] * s),
                 (a.m_v[1] * s) );   
}

vec2 operator*(float s, const vec2 &a) {
    return (a * s);  
}

vec2 operator/(const vec2 &a, const vec2& b) {
    return vec2( (a.m_v[0] / b.m_v[0]),
                 (a.m_v[1] / b.m_v[1]) );   
}

vec2 operator/(const vec2 &a, float s) {
    return (a * (1.0f / s));
}

float vec2::length_squared() const {
    return ( (this->m_v[0] * this->m_v[0]) +
             (this->m_v[1] * this->m_v[1]) );
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
    return ( (a.m_v[0] * b.m_v[0]) +
             (a.m_v[1] * b.m_v[1]) );
}

float vec2::cross(const vec2 &a, const vec2 &b) {
    return ( (a.m_v[0] * b.m_v[1]) - 
             (a.m_v[1] * b.m_v[0]) );
}

float vec2::angle_between(const vec2 &a, const vec2 &b) {
    return acosf(dot(a, b) / M_SQRT(a.length_squared() * b.length_squared()));
}

vec2 vec2::reflect(const vec2 &incident_ray, const vec2 &normal) {
    return incident_ray - (2 * dot(incident_ray, normal) * normal);
}

std::ostream &operator<<(std::ostream& out, const vec2& vec) {
    out << "[" << vec.m_v[0] << ", " << vec.m_v[1] << "]";
    return out;       
}

// VEC3
vec3::vec3(float s) {
    this->m_v[0] = this->m_v[1] = this->m_v[2] = s;
}
vec3::vec3(float x, float y, float z) {
    this->m_v[0] = x; 
    this->m_v[1] = y;
    this->m_v[2] = z;
}

vec3::vec3(const vec3& other) {
    this->m_v[0] = other.m_v[0]; 
    this->m_v[1] = other.m_v[1];
    this->m_v[2] = other.m_v[2];
}

vec3 &vec3::operator=(const vec3& other) {
    if(this != &other) {
        this->m_v[0] = other.m_v[0];
        this->m_v[1] = other.m_v[1];
        this->m_v[2] = other.m_v[2];
    }
    return *this;
}

float &vec3::x() { return this->m_v[0]; }
float &vec3::y() { return this->m_v[1]; }
float &vec3::z() { return this->m_v[2]; }

const float &vec3::x() const { return this->m_v[0]; } 
const float &vec3::y() const { return this->m_v[1]; } 
const float &vec3::z() const { return this->m_v[2]; }     

vec3 vec3::lerp(const vec3 &a, const vec3 &b, const float t) {
    return (a + (b - a) * t);
}

vec3 vec3::clamp(const vec3 &a, const vec3 &min, const vec3 &max) {
    return vec3( clampf(a.m_v[0], min.m_v[0], max.m_v[0]),
                 clampf(a.m_v[1], min.m_v[1], max.m_v[1]), 
                 clampf(a.m_v[2], min.m_v[2], max.m_v[2]) );
}

vec3 vec3::clamp(const vec3 &a, const float min, const float max) {
    return vec3( clampf(a.m_v[0], min, max),
                 clampf(a.m_v[1], min, max), 
                 clampf(a.m_v[2], min, max) );
}

vec3 operator-(const vec3 &a) {
    return vec3(-a.m_v[0], -a.m_v[1], -a.m_v[2]);
}

vec3 operator+(const vec3 &a, const vec3& b) {
    return vec3( (a.m_v[0] + b.m_v[0]), 
                 (a.m_v[1] + b.m_v[1]),
                 (a.m_v[2] + b.m_v[2]) );
}

vec3 operator-(const vec3 &a, const vec3& b) {
    return vec3( (a.m_v[0] - b.m_v[0]), 
                 (a.m_v[1] - b.m_v[1]),
                 (a.m_v[2] - b.m_v[2]) );
}

vec3 operator*(const vec3 &a, const vec3& b) {
    return vec3( (a.m_v[0] * b.m_v[0]), 
                 (a.m_v[1] * b.m_v[1]),
                 (a.m_v[2] * b.m_v[2]) );
}

vec3 operator*(const vec3 &a, float s) {
    return vec3( (a.m_v[0] * s), 
                 (a.m_v[1] * s),
                 (a.m_v[2] * s) );
}

vec3 operator*(float s, const vec3 &a) {
    return (a * s);
}

vec3 operator/(const vec3 &a, const vec3& b) {
    return vec3( (a.m_v[0] / b.m_v[0]), 
                 (a.m_v[1] / b.m_v[1]),
                 (a.m_v[2] / b.m_v[2]) );
}

vec3 operator/(const vec3 &a, float s) {
    return (a * (1.0f / s));
}

float vec3::length_squared() const {
    return ( (this->m_v[0] * this->m_v[0]) + 
             (this->m_v[1] * this->m_v[1]) +
             (this->m_v[2] * this->m_v[2]) );
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
    return ( (a.m_v[0] * b.m_v[0]) +
             (a.m_v[1] * b.m_v[1]) +
             (a.m_v[2] * b.m_v[2]) );
}

vec3 vec3::cross(const vec3 &a, const vec3 &b) {
    return vec3( (a.m_v[1] * b.m_v[2] - a.m_v[2] * b.m_v[1]),
                 (a.m_v[2] * b.m_v[0] - a.m_v[0] * b.m_v[2]),
                 (a.m_v[0] * b.m_v[1] - a.m_v[1] * b.m_v[0]) );
}

float vec3::angle_between(const vec3 &a, const vec3 &b) {
    return acosf(dot(a, b) / M_SQRT(a.length_squared() * b.length_squared()));
}

vec3 vec3::reflect(const vec3 &incident_ray, const vec3 &normal) {
    return incident_ray - (2 * dot(incident_ray, normal) * normal);
}

std::ostream &operator<<(std::ostream& out, const vec3& vec) {
    out << "[" << vec.m_v[0] << ", " << vec.m_v[1] << ", " << vec.m_v[2] << "]";
    return out;
}

// RAY
ray::ray(const vec3 &orig, const vec3 &dir) {
    this-> m_o = orig;
    this-> m_d = dir;
}

ray::ray(const ray &other) {
    this->m_o = other.m_o;
    this->m_d = other.m_d;
}

ray &ray::operator=(const ray &other) {
    if(this != &other) {
        this->m_o = other.m_o;
        this->m_d = other.m_d;
    }
    return *this;
}

vec3 &ray::o() { return this->m_o; }
vec3 &ray::d() { return this->m_d; }

const vec3 &ray::o() const { return this->m_o; }
const vec3 &ray::d() const { return this->m_d; }

vec3 ray::at(const float t) const { 
    return (this->m_o + (this->m_d * t)); 
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

float randf(uint32_t &seed, float min, float max) {
    seed = pcg_hash(seed);
    constexpr uint32_t UINT32_T_MAX = std::numeric_limits<uint32_t>::max();
    float x = ((float)seed / (float)UINT32_T_MAX);
    return min + (x * (max - min));
}

vec2 random_vec2(uint32_t &seed, const float min, const float max) {        
    return vec2( randf(seed, min, max),
                 randf(seed, min, max) );
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
    return vec3( randf(seed, min, max),
                 randf(seed, min, max), 
                 randf(seed, min, max) );
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


