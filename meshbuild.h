#ifndef MESHB
#define MESHB

#include "vec3.h"
#include "ray.h"
#include <vector>

class face {
  private:
    std::vector<vec3> vs;
  public:
    face(std::vector<vec3> vs);
    vec3 equation();
    std::vector<vec3> points();
};

vec3 parse_v(std::string line);
std::vector<face> parse_obj(std::string filename);

#endif
