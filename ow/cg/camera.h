#pragma once

#include "ow/math/vec3.h"
#include "ow/cg/ray.h"
#include <atomic>

namespace ow::cg
{

struct SensorData
{
    float width = 0;
    float height = 0;
    
    SensorData(float width, float height):
        width(width),
        height(height)
    {
    }

    SensorData(){}
};

struct LensData
{
    float focal_length = 0;
    float focus_distance = 0;
    float aperture = 0;

    LensData(float focal_length, float focus_distance, float aperture):
        focal_length(focal_length),
        focus_distance(focus_distance),
        aperture(aperture)
    {
    }

    LensData(){}
};

class Camera
{
public:
    Camera(const math::Vec3f &origin, const math::Vec3f &lookat, const math::Vec3f &up, const SensorData &sensor, const LensData &lens);

    Ray unproject(const math::Vec3f &uv) const;

    void set_fov(const float &focal_length);

private:
    math::Vec3f origin;
    math::Vec3f lower_left_corner;
    math::Vec3f right;
    math::Vec3f up;
    float focal_length;
    float aspect_ratio;
    float viewport_width;
    float viewport_height;
    float aperture;
};

}