#pragma once

#include "ow/math/vec3.h"

#include "hittable.h"

#include <limits>
#include <memory>

namespace ow::cg
{

class Ray;

class Sphere: public Hittable
{
public:
    Sphere(const math::Vec3f &center, const float &radius, std::shared_ptr<Material> material): center(center), radius(radius), material(material) {}

    bool intersect(const Ray &ray, HitRecord &record, const float t_min= 0.0f, const float t_max = std::numeric_limits<float>::infinity()) const override;

    math::Vec3f center;
    float radius;
    std::shared_ptr<Material> material;
};

}