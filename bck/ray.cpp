#include "ray.h"
#include "vec3.h"

//ray::ray(const vec3& v1, const vec3 &v2) : o(v1), e(v2) { }
ray::ray(vec3& v1, vec3 &v2) { o=v1; e=v2; }
vec3 ray::origin() const { return o; }
vec3 ray::direction() const { return e; }

vec3 ray::point(float t) {
  return (o*t)+e;
}
