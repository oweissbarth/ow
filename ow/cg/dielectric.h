#pragma once

#include "material.h"
#include "ow/math/vec3.h"

namespace ow::cg
{

    class HitRecord;
    class Ray;


    class Dielectric: public Material
    {
        public:
        Dielectric(float ior): m_ior(ior) {}

        bool scatter(const Ray &ray, const HitRecord &hit, math::Vec3f &attenuation, Ray &scattered) const override;

        private:
        static float reflectance(float cosine, float ref_index);

        private:
        float m_ior;
    };
}