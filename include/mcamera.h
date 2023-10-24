#ifndef MINI_CAMERA_H
#define MINI_CAMERA_H

#include "./mmath.h"

class Camera {
public:
    Camera() = default;
    Camera(const point3 &orig, const vec3 &look_at, const float vfov, const float aspect_ratio);
    ray cast_ray(const float u, const float v);
private:
    point3 m_origin;
    vec3 m_look_dir;
    vec3 m_camera_local_x;
    vec3 m_camera_local_y;
};

#endif //MINI_CAMERA_H
