#pragma once

#include "ow/math/vec3.h"
#include "ray.h"
#include "material.h"

#include <limits>
#include <memory>

namespace ow::cg
{

struct HitRecord
{
    math::Vec3f pos;
    math::Vec3f normal;
    float t;
    bool front_face;
    std::shared_ptr<Material> material;

    void set_face_normal(const Ray &ray, const math::Vec3f &outward_normal)
    {
        front_face = math::dot(ray.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }   
};


class  Hittable
{
public:
    virtual bool intersect(const Ray &ray, HitRecord &hit_record, const float t_min= 0.0f, const float t_max = std::numeric_limits<float>::infinity()) const = 0;
};

}