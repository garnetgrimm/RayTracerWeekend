#ifndef RAY
#define RAY
#include "vec3.h"

class ray {
  private:
    vec3 o;
    vec3 e;
  public:
    ray(vec3 a, vec3 b);

    vec3 origin();
    vec3 direction();

    vec3 point(float t);
    vec3 equation();

};

inline std::ostream& operator<<(std::ostream &strm, ray r) {
  return strm << "|" << r.origin() << r.direction() << "|";
}

#endif
