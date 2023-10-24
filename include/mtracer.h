#ifndef MINI_TRACER_H
#define MINI_TRACER_H

#include <fstream>
#include "./mmath.h"
#include "./mcamera.h"

class Mini_Tracer {
public:
    Mini_Tracer(const size_t width, const size_t height, 
                const point3 &cam_orig, const point3 &cam_look_at, const float cam_vfov);
    void render_scene();
    void postprocess();
    void save_as_ppm(const char *file_name);
    ~Mini_Tracer();

private:
    color3 per_pixel(const vec2 &pixelCoord);

private:
    size_t m_width;
    size_t m_height;
    color3 *m_img_buffer;
    uint32_t m_rseed;
    Camera m_camera;
};

#endif // MINI_TRACER_H

