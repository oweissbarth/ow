#include "image.h"

#include "ow/math/utils.h"

#include <iostream>
#include <fstream>
#include <cassert>

namespace ow::cg
{


Image::Image(int imWidth, int imHeight): m_width(imWidth), m_height(imHeight)
{
    m_pixels.resize(3*m_width*m_height);
}

Image::Image(int imWidth, int imHeight, const std::span<float>& pixels): m_width(imWidth), m_height(imHeight)
{
    m_pixels.reserve(3*m_width*m_height);
    m_pixels.assign(pixels.begin(), pixels.end());
}

bool Image::savePPM(const std::string& path) const
{
    std::ofstream file;
    file.open(path);
    if(!file.is_open()){
        return false;
    }

    file << "P3\n" << m_width << " " << m_height << "\n255\n";

    for(int i = m_height-1; i >= 0; --i)
    {
        for(int j = 0 ; j < m_width; ++j)
        {
            math::Vec3f p = get(j, i);
            int ir = static_cast<int>(256 * math::clamp(p.r, 0.0f, 0.999));
            int ig = static_cast<int>(256 * math::clamp(p.g, 0.0f, 0.999));
            int ib = static_cast<int>(256 * math::clamp(p.b, 0.0f, 0.999));
            assert(0 <= ir && ir <= 256);
            assert(0 <= ig && ig <= 256);
            assert(0 <= ib && ib <= 256);
            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    file.close();
    return true;
}

math::Vec3f Image::get(const int x, const int y) const 
{
    int base = 3*(y*m_width+x);
    return math::Vec3f(m_pixels[base], m_pixels[base+1], m_pixels[base+2]);
}

void Image::set(const int x, const int y, math::Vec3f pixel) 
{
    std::scoped_lock<std::mutex> lock(m_lock);
    int base = 3*(y*m_width+x);
    m_pixels[base    ] = pixel.x;
    m_pixels[base + 1] = pixel.y;
    m_pixels[base + 2] = pixel.z;
}

int Image::get_width() const
{
    return m_width;
}
int Image::get_height() const
{
    return m_height;
}

const float* Image::data() const
{
    return m_pixels.data();

}
} // namespace ow::cg