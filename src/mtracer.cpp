#include "../include/mtracer.h"

Mini_Tracer::Mini_Tracer(const size_t width, const size_t height, 
                         const point3 &cam_orig, const point3 &cam_look_at, const float cam_vfov) 
{
    m_width = width; 
    m_height = height; 
    m_img_buffer = new color3[width * height];
    m_rseed = time(static_cast<unsigned>(NULL)); 
    m_camera = Camera(cam_orig, cam_look_at, cam_vfov, ((float)width / (float)height));
}

Mini_Tracer::~Mini_Tracer() {
    delete [] this->m_img_buffer;
}

color3 Mini_Tracer::per_pixel(const vec2 &pixelCoord) {
    vec2 uv = pixelCoord / vec2(m_width - 1, m_height - 1);
    ray r = m_camera.cast_ray(uv.x(), uv.y());
    return vec3::clamp(r.d(), 0, 1);
    //return color3(randf(m_rseed, 0, 1), randf(m_rseed, 0, 1), randf(m_rseed, 0, 1));
}

void Mini_Tracer::render_scene() {
    uint32_t p = 0;
    std::cout << "[INFO] Starting Render....\n";
    for(size_t y = 0; y < m_height; ++y) {
        p = (uint32_t)( ( (float)y / (float)(m_height - 1) ) * 100.0f ); 
        std::cout << "\r[INFO] Rendering : " << p << "%" << std::flush;
        for(size_t x = 0; x < m_width; ++x) { 
            m_img_buffer[x + y * m_width] = this->per_pixel(vec2(x, y));
        }
    }
    std::cout << "\n";
}

void Mini_Tracer::postprocess() {
    for(size_t i = 0; i < m_width * m_height; ++i) 
    {
        vec3 &pixc = m_img_buffer[i];
        // gamma 2.0 correction
        pixc.x() = M_SQRT(pixc.x());
        pixc.y() = M_SQRT(pixc.y());
        pixc.z() = M_SQRT(pixc.z());
        // clamping between 0 and 1 
        pixc = vec3::clamp(pixc, 0, 1);
    }
}

void Mini_Tracer::save_as_ppm(const char *file_name) {
    std::cout << "[INFO] Saving render as PPM image : " << file_name << "\n";
    std::fstream f(file_name, std::ios::out);
    if(!f.is_open()) {
        std::cerr << "[ERROR] COULD NOT OPEN FILE : " << file_name << "\n";
        exit(1);
    }
    f << "P3\n" << m_width << " " << m_height << "\n255\n";
    for(size_t i = 0; i < m_width * m_height; ++i) {
        vec3 &pixc = m_img_buffer[i];
        f << static_cast<size_t>(pixc.x() * 255.999f) << " " 
          << static_cast<size_t>(pixc.y() * 255.999f) << " " 
          << static_cast<size_t>(pixc.z() * 255.999f) << "\n";
    }
}

