#pragma once

#include "ow/math/vec3.h"

namespace ow::cg
{

class HitRecord;
class Ray;

class Material
{
    public:
    virtual bool scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const = 0;
};
}