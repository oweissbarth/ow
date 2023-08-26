#pragma once

#include "hittable.h"

#include <vector>
#include <memory>

namespace ow::cg
{

class HittableList: public Hittable
{
public:
    HittableList(){};

    void add(const std::shared_ptr<Hittable> hitable);

    bool intersect(const Ray &ray, HitRecord &hit_record, const float t_min= 0.0f, const float t_max = std::numeric_limits<float>::infinity()) const override;
private:
    std::vector<std::shared_ptr<Hittable>> m_hittables;
};

}