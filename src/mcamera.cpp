#include "../include/mcamera.h"

Camera::Camera(const point3 &origin, const vec3 &look_dir, float vfov, float aspect_ratio) {
    this->vfov  = vfov;
    float vhalf = vfov / 2.0f;
    this->viewport_height = 2.0f * tanf(vhalf);
    this->viewport_width  = this->viewport_height * aspect_ratio;
    this->aspect_ratio = aspect_ratio;
    this->origin   = origin;
    this->look_dir = look_dir;

    vec3 world_up = vec3(0.0f, 1.0f, 0.0f);
    this->u = vec3::normalize(vec3::cross(world_up, look_dir));
    this->v = vec3::cross(look_dir, this->u);
 
    this->u = this->u * (this->viewport_width  * 0.5f);   
    this->v = this->v * (this->viewport_height * 0.5f);
}
 
ray Camera::get_ray(const float su, const float sv) {
    return ray( this->origin, 
                vec3::normalize((su * this->u) + (sv * this->v) + this->look_dir) );
}
