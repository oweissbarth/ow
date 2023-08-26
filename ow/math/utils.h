#pragma once

namespace ow::math
{
    float clamp(float x, float min, float max);

    bool equals(float a, float b, float epsilon = 1e-5);

    float radians(float degrees);

    float degrees(float radians);
}

