#pragma once

#include "ow/math/vec3.h"

#include <vector>
#include <string>
#include <mutex>

namespace ow::cg
{

class Image
{
public:

    Image(const int width, const int height);

    bool savePPM(const std::string path);

    math::Vec3f get(const int x, const int y) const;
    void set(const int x, const int y, const math::Vec3f pixel);

    int get_width() const;
    int get_height() const;

private:
    const int width;
    const int height;
    std::vector<float> pixels;

    std::mutex m_lock;

};

}