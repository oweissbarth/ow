#include "utils.h"

#include <cmath>

namespace ow::math
{
    float clamp(float x, float min, float max)
    {
        if(x < min ) return min;
        if(x > max) return max;
        return x;
    }

    bool equals(float a, float b, float epsilon)
    {
        return std::fabs(a - b) < epsilon;
    }

    float radians(float degrees)
    {
        return degrees * M_PI / 180.0f;
    }

    float degrees(float radians)
    {
        return radians * 180.0f / M_PI;
    }
}
