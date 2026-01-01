#include <iostream>
#include <cmath>
#include <limits>
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "hitable_list.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"

vec3 color(const ray& r, const hittable* world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        return vec3(0.0f, 0.0f, 0.0f);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100; // samples per pixel for anti-aliasing
    std::cout << "P3\n" << nx <<" " << ny << "\n255\n";
    // Scene: matte center sphere, matte ground, metal spheres on left/right
    material* mat_center = new lambertian(vec3(0.1f, 0.2f, 0.5f));
    material* mat_ground = new lambertian(vec3(0.8f, 0.8f, 0.0f));
    material* mat_metal_left = new metal(vec3(0.8f, 0.8f, 0.8f), 0.0f);
    material* mat_metal_right = new metal(vec3(0.8f, 0.6f, 0.2f), 0.3f);
    hittable* list[4];
    list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, mat_center);
    list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, mat_ground);
    list[2] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, mat_metal_left);
    list[3] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, mat_metal_right);
    hittable* world = new hittable_list(list, 4);

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; s++) {
                float u = (float(i) + random_float()) / float(nx);
                float v = (float(j) + random_float()) / float(ny);
                ray r(origin, lower_left_corner + u * horizontal + v * vertical);
                col += color(r, world, 0);
            }
            col /= float(ns);
            int ir = int(255.99f * col[0]);
            int ig = int(255.99f * col[1]);
            int ib = int(255.99f * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    delete list[0];
    delete list[1];
    delete list[2];
    delete list[3];
    delete world;
    delete mat_center;
    delete mat_ground;
    delete mat_metal_left;
    delete mat_metal_right;
}
