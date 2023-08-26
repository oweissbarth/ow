#include "diffuse.h"
#include "ray.h"
#include "hittable.h"
#include "sampler.h"



namespace ow::cg
{
    bool Diffuse::scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const
    {
        math::Vec3f scatter_direction = hit.normal + random_unit_vector();
        if(scatter_direction.near_zero())
            scatter_direction = hit.normal;
        scattered = Ray(hit.pos, scatter_direction.normalized());
        attenuation = m_albedo;
        return true;
    }
}