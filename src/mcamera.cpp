#include "../include/mcamera.h"

Camera::Camera(const point3 &orig, const vec3 &look_at, const float vfov, const float aspect_ratio) {
    float viewport_height = 2.0f * tanf(vfov * 0.5f);
    float viewport_width  = aspect_ratio * viewport_height;
    m_origin = orig;
    m_look_dir = vec3::normalize(look_at - orig);
    vec3 camera_local_i = vec3::normalize(vec3::cross(m_look_dir, vec3(0.0f, 1.0f, 0.0f)));
    vec3 camera_local_j = vec3::cross(camera_local_i, m_look_dir);
    m_camera_local_x = camera_local_i * (viewport_width  * 0.5);
    m_camera_local_y = camera_local_j * (viewport_height * 0.5);
}

ray Camera::cast_ray(const float u, const float v) {
    float su = (u * 2.0f) - 1.0f;
    float sv = 1.0f - (v * 2.0f);
    return ray(m_origin,
               vec3::normalize(su * m_camera_local_x + sv * m_camera_local_y + m_look_dir));
}
