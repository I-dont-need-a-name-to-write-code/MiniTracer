#include "../include/mobject.h"

// Objects
Object::Object(Object_Type type, void *p_obj) {
    this->type  = type;
    this->p_obj = p_obj;
}

Sphere::Sphere(const point3 &origin, const float radius) {
    this->m_r = radius;
    this->m_o = origin;
}

void Sphere::set_material(Material_Type type, void *p_mat) {
    this->m_mat.type  = type;
    this->m_mat.p_mat = p_mat;
}

float    &Sphere::r() { return this->m_r; }
point3   &Sphere::o() { return this->m_o; }
Material &Sphere::mat() { return this->m_mat;}

const float    &Sphere::r() const { return this->m_r; }
const point3   &Sphere::o() const { return this->m_o; }
const Material &Sphere::mat() const { return this->m_mat;}

Hit_Info Sphere::hit(const Sphere &sphere, const ray &r) 
{
    vec3 sr = r.o() - sphere.o();
    float a = vec3::dot(r.d(), r.d());
    float b = 2 * vec3::dot(r.d(), sr);
    float c = vec3::dot(sr, sr) - sphere.r() * sphere.r();
    
    Hit_Info info;

    float d = b * b - 4 * a * c;
    if(d < 0.0f) {
        info.is_hit = false;
        return info;
    }

    float sqrt_d = sqrtf(d);
    float t = (-b - sqrt_d) / (2 * a);
    if(t < 0.0f) {
        t = (-b + sqrt_d) / (2 * a);
        if(t < 0.0f) {
            info.is_hit = false;
            return info;
        }
    }

    info.is_hit = true;
    info.t = t;
    info.hit_point = r.at(t);
    info.mat = sphere.mat();

    vec3 normal = (info.hit_point - sphere.o()) / sphere.r();
    if(vec3::dot(r.d(), normal) > 0.0f) {
        normal = -normal;
    }
    info.normal = normal;

    return info;
}

Triangle::Triangle(const point3 &p0,
                   const point3 &p1,
                   const point3 &p2)
{
    this->m_p[0] = p0;
    this->m_p[1] = p1;
    this->m_p[2] = p2;
}

void Triangle::set_material(Material_Type type, void *p_mat) {
    this->m_mat.type  = type;
    this->m_mat.p_mat = p_mat;
}
    
point3   &Triangle::p0()  { return this->m_p[0]; }
point3   &Triangle::p1()  { return this->m_p[1]; }
point3   &Triangle::p2()  { return this->m_p[2]; }
Material &Triangle::mat() { return this->m_mat;  }

const point3   &Triangle::p0()  const { return this->m_p[0]; }
const point3   &Triangle::p1()  const { return this->m_p[1]; }
const point3   &Triangle::p2()  const { return this->m_p[2]; }
const Material &Triangle::mat() const { return this->m_mat;  }

Hit_Info Triangle::hit(const Triangle &triangle, const ray &r) {
    (void)triangle;
    (void)r;
    return Hit_Info {};
}


// Material
Material::Material(Material_Type type, void *p_mat) {
    this->type  = type;
    this->p_mat = p_mat;
}

Lambertian::Lambertian(const color3& albedo) {
    this->m_albedo = albedo;
}

color3 &Lambertian::albedo() { return this->m_albedo; }
const color3 &Lambertian::albedo() const { return this->m_albedo; }
    
ray Lambertian::scatter(const Lambertian &material, const Hit_Info &hit_info, uint32_t &rng_state) {
    (void)material;
    point3 ray_origin = hit_info.hit_point + (hit_info.normal * 0.01);
    vec3   ray_dir    = vec3::normalize(hit_info.normal + random_in_unit_sphere(rng_state));
    return ray(ray_origin, ray_dir);
}

Emissive::Emissive(const color3 emission_color, const float emission_strength) {
    this->m_emission_color    = emission_color;
    this->m_emission_strength = emission_strength;
}

color3 &Emissive::emission_color() { return this->m_emission_color; }
float  &Emissive::emission_strength() { return this->m_emission_strength; }

const color3 &Emissive::emission_color() const { return this->m_emission_color; }
const float  &Emissive::emission_strength() const { return this->m_emission_strength; }

