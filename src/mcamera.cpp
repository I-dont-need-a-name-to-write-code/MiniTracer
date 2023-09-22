#include "../include/mcamera.h"

Camera::Camera(const point3 &origin, const vec3 &look_at, float vfov, float aspect_ratio) {
    this->m_vfov  = vfov;
    float vhalf = vfov / 2.0f;
    this->m_viewport_height = 2.0f * tanf(vhalf);
    this->m_viewport_width  = this->m_viewport_height * aspect_ratio;
    this->m_aspect_ratio = aspect_ratio;
    this->m_origin   = origin;
    this->m_look_dir = vec3::normalize(look_at - origin);

    vec3 world_up = vec3(0.0f, 1.0f, 0.0f);
    this->m_u = vec3::normalize(vec3::cross(world_up, this->m_look_dir));
    this->m_v = vec3::cross(this->m_look_dir, this->m_u);

    this->m_u = this->m_u * (this->m_viewport_width  * 0.5f);   
    this->m_v = this->m_v * (this->m_viewport_height * 0.5f);
}
 
ray Camera::get_ray(const float su, const float sv) {
    return ray( this->m_origin, 
                vec3::normalize((su * this->m_u) + (sv * this->m_v) + this->m_look_dir) );
}
