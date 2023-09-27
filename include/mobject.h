#ifndef MINI_OBJECT_H
#define MINI_OBJECT_H

#include "./mmath.h"

enum class Object_Type {
    DEFAULT,
    SPHERE,
    TRIANGLE
};

class Object {
public:
    Object() = default;
    Object(Object_Type type, void *p_obj);
public:
    const void *p_obj = nullptr;
    Object_Type type = Object_Type::DEFAULT;
};

enum class Material_Type {
    DEFAULT,
    LAMBERTIAN,
    EMISSIVE,
    METAL,
    GLASS
};

class Material {
public:
    Material() = default;
    Material(Material_Type type, void *p_mat);
public:
    const void *p_mat = nullptr;
    Material_Type type = Material_Type::DEFAULT;
}; 

class Hit_Info {
public:
    bool     is_hit;
    float    t;
    point3   hit_point;
    vec3     normal;
    Material mat;
};

// Objects

class Sphere {
public:
    Sphere() = default;
    Sphere(const point3 &origin, const float radius);
    
    // getter and setter
    void set_material(Material_Type type, void *p_mat);
    
    float    &r(); 
    point3   &o(); 
    Material &mat();

    const float    &r() const; 
    const point3   &o() const; 
    const Material &mat() const;

    // ray hit intersection
    static Hit_Info hit(const Sphere &sphere, const ray &r);

private:
    float    m_r;
    point3   m_o;
    Material m_mat;
};  

class Triangle {
public:
    Triangle() = default;
    Triangle(const point3   &p0,
             const point3   &p1,
             const point3   &p2);
    
    // getter and setter
    void set_material(Material_Type type, void *p_mat);

    point3   &p0();
    point3   &p1();
    point3   &p2();
    Material &mat();

    const point3   &p0()  const;
    const point3   &p1()  const;
    const point3   &p2()  const;
    const Material &mat() const;

    // ray hit intersection
    static Hit_Info hit(const Triangle &triangle, const ray &r);

private:
    point3   m_p[3];
    Material m_mat;
};


// Material 

class Lambertian {
public:
    Lambertian() = default;
    Lambertian(const color3 &albedo);
    
    // getter and setter
    color3 &albedo(); 
    const color3 &albedo() const; 

    // scatter function
    static ray scatter(const Lambertian &material, const Hit_Info &hit_info, uint32_t &rng_state);

private:
    color3 m_albedo;
};

class Emissive {
public:
    Emissive() = default;
    Emissive(const color3 emission_color, const float emission_strength);

    // getter and setter
    color3 &emission_color(); 
    float  &emission_strength();

    const color3 &emission_color() const; 
    const float  &emission_strength() const; 

private:
    color3 m_emission_color;
    float  m_emission_strength;
};

#endif // MINI_OBJECT_H


