#include "camera.h"
#include "ray.h"
#include "sampler.h"

#include "ow/math/vec3.h"


namespace ow::cg
{

Camera::Camera(const math::Vec3f &origin, const math::Vec3f &lookat, const math::Vec3f &up_dir, const SensorData &sensor, const LensData &lens)
: origin(origin)
, focal_length(lens.focal_length)
, aspect_ratio(sensor.width/sensor.height)
, aperture(lens.aperture)
{
    auto w = (origin - lookat).normalized();
    auto u = cross(up_dir, w);
    auto v = cross(w, u);

    viewport_height = sensor.height;
    viewport_width = sensor.width;

    right = u*lens.focus_distance * 1.0F/focal_length;
    up =  v*lens.focus_distance * 1.0F/focal_length;
    lower_left_corner = origin  - right*viewport_width/2.0F  - up*viewport_height/2.0F - w*lens.focus_distance;
}


Ray Camera::unproject(const math::Vec3f &pos) const
{
    math::Vec3f rnd = aperture * random_in_unit_disk();
    math::Vec3f offset = right * rnd.x +  up * rnd.y;
    math::Vec3f direction((lower_left_corner +  pos.x*right*viewport_width + pos.y*up*viewport_height) - origin - offset);

    return {origin+offset, direction.normalized()};
}

}