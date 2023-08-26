#include "image.h"

#include "ow/math/utils.h"

#include <iostream>
#include <fstream>
#include <cassert>

namespace ow::cg
{


Image::Image(const int imWidth, const int imHeight): width(imWidth), height(imHeight)
{
    pixels.resize(3*width*height);
}

bool Image::savePPM(const std::string path)
{
    std::ofstream file;
    file.open(path);
    if(!file.is_open()){
        return false;
    }

    file << "P3\n" << width << " " << height << "\n255\n";

    for(int i = height-1; i >= 0; --i)
    {
        for(int j = 0 ; j < width; ++j)
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
    int base = 3*(y*width+x);
    return math::Vec3f(pixels[base], pixels[base+1], pixels[base+2]);
}

void Image::set(const int x, const int y, math::Vec3f pixel) 
{
    std::scoped_lock<std::mutex> lock(m_lock);
    int base = 3*(y*width+x);
    pixels[base    ] = pixel.x;
    pixels[base + 1] = pixel.y;
    pixels[base + 2] = pixel.z;
}

int Image::get_width() const
{
    return width;
}
int Image::get_height() const
{
    return height;
}

}