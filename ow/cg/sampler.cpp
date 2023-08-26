#include "sampler.h"

#include "ow/math/vec3.h"


#ifdef OW_WITH_PCG
    #include "pcg_random.hpp"
#endif

#include <random>

namespace ow::cg
{


float random_float(float min, float max)
{
#ifdef OW_WITH_PCG
    static pcg_extras::seed_seq_from<std::random_device> seed_source;
    static pcg32 rng(seed_source);
    static std::uniform_real_distribution<float> uniform_dist(min, max);
    return uniform_dist(rng);
#else
    static std::uniform_real_distribution<float>dist(0,1);
    static std::mt19937 generator;
    return dist(generator);
#endif
}


math::Vec3f random(float min, float max)
{
    return math::Vec3f(random_float(min, max), random_float(min, max), random_float(min, max));
}

math::Vec3f random_in_unit_sphere()
{
    while (true) {
        auto p = math::Vec3f(random_float()*2-1.0, random_float()*2-1.0, random_float()*2-1.0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

math::Vec3f random_in_unit_disk()
{
    while (true) {
        auto p = math::Vec3f(random_float()*2-1.0, random_float()*2-1.0, 0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

math::Vec3f random_unit_vector()
{
    return random_in_unit_sphere().normalized();
}

math::Vec3f random_in_hemisphere(const math::Vec3f &normal)
{
    math::Vec3f in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0f)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

    
}