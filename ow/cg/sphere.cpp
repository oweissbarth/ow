#include "sphere.h"
#include "ow/math/vec3.h"
#include "ray.h"

#include <cmath>

namespace ow::cg
{

    bool Sphere::intersect(const Ray &ray, HitRecord &record, const float t_min, const float t_max) const
    {
        math::Vec3f oc(ray.origin - center);
        float a = ray.direction.lengthSquared();
        float half_b = math::dot(oc, ray.direction);
        float c = oc.lengthSquared() - radius * radius;

        float discriminant = half_b*half_b  - a*c;
        if( discriminant < 0.0f)
            return false;
        
        float sqrtd = std::sqrt(discriminant);
        float root = (-half_b -sqrtd)/a;
        
        if(root < t_min || t_max < root){
            root = (-half_b + sqrtd)/a;
            if(root <t_min || t_max < root){
                return false;
            }
        }
        record.pos = ray.at(root);
        record.t = root;
        math::Vec3f outward_normal = (record.pos - center)/radius;
        record.set_face_normal(ray, outward_normal);
        record.material = material;
        return true;

    }
}