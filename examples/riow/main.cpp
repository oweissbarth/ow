#include "ow/cg/image.h"
#include "ow/cg/ray.h"
#include "ow/cg/camera.h"
#include "ow/cg/sphere.h"
#include "ow/cg/sampler.h"
#include "ow/cg/hittable_list.h"
#include "ow/cg/hittable.h"
#include "ow/cg/diffuse.h"
#include "ow/cg/metal.h"
#include "ow/cg/dielectric.h"
#include "ow/utils/threadpool.h"

#include <iostream>
#include <memory>
#include <cmath>
#include <limits>
#include <unistd.h>

using namespace ow;

math::Vec3f background(const cg::Ray &ray)
{
    float t = 0.5*(ray.direction.y + 1.0);
    return (1-t)  * math::Vec3f(1.0, 1.0, 1.0)  + t * math::Vec3f(0.5, 0.7, 1.0);
}

math::Vec3f ray_color(const cg::Ray &ray, const cg::Hittable &hitable, int depth)
{
    if(depth <= 0)
    {
        return {0, 0, 0};
    }
    cg::HitRecord record;
    bool hit = hitable.intersect(ray, record, 0.001, std::numeric_limits<float>::infinity());
    if(hit)
    {
        math::Vec3f attenuation;
        cg::Ray scattered;
        if(record.material->scatter(ray, record, attenuation, scattered)) 
        {
            return attenuation * ray_color(scattered, hitable, depth-1);
        }
        return {0,0,0};
    }
    return background(ray);
}


void trace_pixel(math::Vec3f pixel, const cg::Camera &cam, const int samples_per_pixel, const cg::Hittable &world, cg::Image &im)
{
    math::Vec3f c;
    for(int s = 0; s < samples_per_pixel; ++s)
    {
        auto r = (float(pixel.x)+cg::random_float())/im.get_width();
        auto g = (float(pixel.y)+cg::random_float())/im.get_height();
        math::Vec3f p(r, g, 0);
        cg::Ray ray = cam.unproject(p);
        c += ray_color(ray, world, 20);

    }
    
    c.g = std::sqrt(c.g/float(samples_per_pixel));
    c.r = std::sqrt(c.r/float(samples_per_pixel));
    c.b = std::sqrt(c.b/float(samples_per_pixel));
    im.set(pixel.x, pixel.y, c);
}

cg::HittableList final_scene()
{
    cg::HittableList world;
    auto material_ground = std::make_shared<cg::Diffuse>(math::Vec3f(0.5f, 0.5f, 0.5f));
    world.add(std::make_shared<cg::Sphere>(math::Vec3f(0.0,-1000, 0),  1000, material_ground));

    for(int a = -11; a < 11; ++a)
    {
        for(int b = -11; b < 11; ++b)
        {
            float mat_random = cg::random_float();
            math::Vec3f position(a + 0.9 * cg::random_float(), 0.2, b + 0.9 * cg::random_float());
            if((position -  math::Vec3f(4,0.2,0)).length() > 0.9)
            {
                std::shared_ptr<cg::Material> sphere_mat;
                if(mat_random < 0.8)
                {
                    sphere_mat = std::make_shared<cg::Diffuse>(cg::random()*cg::random());
                }else if(mat_random < 0.95)
                {
                    sphere_mat = std::make_shared<cg::Metal>(cg::random(0.5, 1), cg::random_float(0, 0.5));
                }else
                {
                    sphere_mat = std::make_shared<cg::Dielectric>(1.5);
                }
                std::cout << "adding sphere" << std::endl;
                world.add(std::make_shared<cg::Sphere>(position, 0.2, sphere_mat));
            }
        }
    }
    std::shared_ptr<cg::Material> mat1 = std::make_shared<cg::Dielectric>(1.5);
    world.add(std::make_shared<cg::Sphere>(math::Vec3f(0,1,0), 1.0, mat1));

    std::shared_ptr<cg::Material> mat2 = std::make_shared<cg::Diffuse>(math::Vec3f(0.4,0.2,0.1));
    world.add(std::make_shared<cg::Sphere>(math::Vec3f(-4,1,0), 1.0, mat2));

    std::shared_ptr<cg::Material> mat3 = std::make_shared<cg::Metal>(math::Vec3f(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<cg::Sphere>(math::Vec3f(4,1,0), 1.0, mat3));


    return world;
}

int main(){
    /*const int imWidth = 600;
    const int imHeight = 400;*/
    const int imWidth = 1500;
    const int imHeight = 1000;

    cg::Image im(imWidth, imHeight);

    math::Vec3f cam_pos = math::Vec3f(13,2,3);
    math::Vec3f lookat = math::Vec3f(0,0, 0);
    cg::Camera cam(cam_pos, lookat, math::Vec3f(0,1,0), cg::SensorData(35.6, 23.8), cg::LensData(50, 10.0 , 0.8));

    cg::HittableList world = final_scene();

    int samples_per_pixel = 500;

    utils::ThreadPool pool;

    for(int i = 0; i < imWidth; ++i)
    {
        for(int j = 0; j< imHeight; ++j)
        {
            math::Vec3f pixel(i, j, 0.f);
            auto job = [pixel, &cam, samples_per_pixel, &world, &im](){trace_pixel(pixel, cam, samples_per_pixel, world, im);};
            pool.add_job(job);
        }
    }

    while(pool.has_work())
    {
        float done = imWidth*imHeight - (float)pool.get_remaining();
        float percentage = done/(imWidth*imHeight);
        std::cout << percentage*100 << "%" << std::endl;
        sleep(1);
    }

    pool.join();
    im.savePPM("result.ppm");
}


