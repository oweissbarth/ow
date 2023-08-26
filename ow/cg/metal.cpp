#include "metal.h"
#include "ow/math/vec3.h"

#include "hittable.h"
#include "ray.h"

namespace ow::cg
{
    bool Metal::scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const
    {
        math::Vec3f reflected_direction = reflect(ray.direction, hit.normal);
        scattered = Ray(hit.pos, (reflected_direction + m_roughness*random_in_unit_sphere()).normalized());
        attenuation = m_albedo;
        return dot(scattered.direction, hit.normal)> 0;
    }
}