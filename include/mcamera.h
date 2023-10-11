#ifndef MINI_CAMERA_H
#define MINI_CAMERA_H

#include <cstdint>
#include "./mmath.h"

class Camera {
public:
    Camera() = default;
    Camera(const point3 &origin, const vec3 &look_at, float vfov, float aspect_ratio);

    // su range [-1, 1] && sv range [1, -1]
    ray get_ray(const float su, const float sv);

private:
    float  m_vfov;
    float  m_viewport_width;
    float  m_viewport_height;
    float  m_aspect_ratio;
    point3 m_origin;
    vec3   m_look_dir;
    vec3   m_u, m_v;
};

#endif // MINI_CAMERA_H



