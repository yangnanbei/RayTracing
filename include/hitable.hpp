#pragma once

#include "ray.hpp"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    class material* mat_ptr;
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
