#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "hitable_list.hpp"
#include "sphere.hpp"

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline float random_float() {
    return rand() / (RAND_MAX + 1.0f);
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0f * vec3(random_float(), random_float(), random_float()) - vec3(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0f);
    return p;
}

vec3 color(const ray& r, const hittable* world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec)) {
        if (depth >= 50) {
            return vec3(0.0f, 0.0f, 0.0f);
        }
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5f * color(ray(rec.p, target - rec.p), world, depth + 1);
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
    // Scene: small sphere in front and large ground sphere
    hittable* list[2];
    list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);
    hittable* world = new hittable_list(list, 2);

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
    delete world;
}
