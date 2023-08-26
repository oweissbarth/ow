#include "hittable_list.h"

namespace ow::cg
{

bool HittableList::intersect(const Ray &ray, HitRecord &hit_record, const float t_min, const float t_max) const
{
    HitRecord current;

    bool first = true;
    bool any_hit = false;

    for(auto h : m_hittables)
    {
        bool hit =  h->intersect(ray, current, t_min, t_max);
        if(hit && (first || current.t < hit_record.t))
        {
            first = false;
            any_hit = true;
            hit_record = current;
        }
    }
    return any_hit;
}


void HittableList::add(const std::shared_ptr<Hittable> hitable)
{
    m_hittables.emplace_back(hitable);
}

}

