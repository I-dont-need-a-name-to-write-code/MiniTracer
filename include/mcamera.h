#ifndef MINI_CAMERA_H
#define MINI_CAMERA_H

#include "./mmath.h"

class Camera {
public:
    Camera() = default;
    Camera(const point3 &origin, const vec3 &look_at, float vfov, float aspect_ratio);

    // su range [-1, 1] && sv range [1, -1]
    ray get_ray(const float su, const float sv);

private:
    float  vfov;
    float  viewport_width;
    float  viewport_height;
    float  aspect_ratio;
    point3 origin;
    vec3   look_dir;
    vec3   u, v;
};

#endif // MINI_CAMERA_H



