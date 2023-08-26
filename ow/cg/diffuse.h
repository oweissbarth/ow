#pragma once

#include "material.h"
#include "ow/math/vec3.h"

namespace ow::cg
{

class HitRecord;
class Ray;

class Diffuse: public Material
{
public:
    Diffuse(const math::Vec3f &albedo): m_albedo(albedo){}

    bool scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const override;

private:
    math::Vec3f m_albedo;
};
}

