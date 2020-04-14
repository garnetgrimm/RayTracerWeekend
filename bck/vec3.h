#ifndef VEC3
#define VEC3

#include <ostream>

using namespace std;

class vec3 {
private:
  float xyz[3] = {1,1,1};
public:
  vec3();
  vec3(float x, float y, float z);
  float x();
  float y();
  float z();
  vec3 cross(vec3 &v1, vec3 &v2);
  vec3 unit_vector();
  float length();

  vec3 operator+(vec3 v);
  vec3 operator+=(vec3 v);
  vec3 operator-(vec3 v);
  float operator*(vec3 v);
  vec3 operator*(float q);

};

inline std::ostream& operator<<(std::ostream &strm, vec3 v) {
  return strm << "<" << v.x() << "," << v.y() << "," << v.z() << ">";
}

#endif
