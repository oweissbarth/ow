#pragma once

#include "ow/math/vec3.h"

#include <vector>
#include <string>
#include <span>
#include <mutex>

namespace ow::cg
{

class Image
{
public:

    Image(int width, int height);

    Image(int width,  int height, const std::span<float>& pixels);

    [[nodiscard]] bool savePPM(const std::string& path) const;

    [[nodiscard]] math::Vec3f get(int x, int y) const;
    void set(int x, int y, math::Vec3f pixel);

    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;

    [[nodiscard]] const float* data() const;

private:
    const int m_width;
    const int m_height;
    std::vector<float> m_pixels;

    std::mutex m_lock;

};

}