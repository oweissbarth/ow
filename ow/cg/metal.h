#pragma once

#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "sampler.h"
#include "ow/math/vec3.h"

namespace ow::cg
{
class Metal: public Material
{
public:
    Metal(const math::Vec3f &albedo, const float roughness): m_albedo(albedo), m_roughness(roughness){}

    bool scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const override;

private:
    math::Vec3f m_albedo;
    float m_roughness;
};
}

