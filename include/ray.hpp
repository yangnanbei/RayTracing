#pragma once

#include "vec3.hpp"

class ray {
public:
    ray() = default;
    ray(const vec3& origin, const vec3& direction) : A(origin), B(direction) {}

    inline vec3 origin() const { return A; }
    inline vec3 direction() const { return B; }
    inline vec3 point_at_parameter(float t) const { return A + t * B; }

private:
    vec3 A;
    vec3 B;
};
