#include "dielectric.h"
#include "ray.h"
#include "hittable.h"
#include "sampler.h"

#include <cmath>

namespace ow::cg
{
    bool Dielectric::scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const
    {
        attenuation = math::Vec3f(1.0f, 1.0f, 1.0f);
        float refraction_ratio = hit.front_face ? (1.0f/m_ior) : m_ior;

        float cos_theta = std::fmin(math::dot(ray.direction, hit.normal), 1.0);
        float sin_theta = std::sqrt(1.0f - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        math::Vec3f direction;
        if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
            direction = reflect(ray.direction, hit.normal);
        else
            direction = refract(ray.direction, hit.normal, refraction_ratio);
        scattered = Ray(hit.pos, direction.normalized());
        return true;
    }

    float Dielectric::reflectance(float cosine, float ref_index)
    {
        float r0 = (1.0f - ref_index) / (1.0f + ref_index);
        r0 = r0 * r0;
        return r0 + (1.0f - r0)* std::pow(1.0f - cosine, 5.0f);
    }

}