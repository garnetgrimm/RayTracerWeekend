#include "vec3.h"
#include "math.h"

vec3::vec3(){}

vec3::vec3(float x, float y, float z)
{xyz[0] = x; xyz[1] = y; xyz[2] = z; equals=0; }

vec3::vec3(float x, float y, float z, float e)
{xyz[0] = x; xyz[1] = y; xyz[2] = z; equals=e; }

float vec3::x() { return xyz[0]; };
float vec3::y() { return xyz[1]; };
float vec3::z() { return xyz[2]; };

float vec3::length() {
  //-> is like . but for pointers
  return sqrt((x()*x())+(y()*y())+(z()*z()));
}

vec3 vec3::setEquals(float e) {
  return vec3(x(), y(), z(), e);
}

vec3 vec3::cross(vec3 v) {
  return vec3(
      y()*v.z() - z()*v.y(),
   (-(x()*v.z() - z()*v.x())),
     (x()*v.y() - y()*v.x()));
 }


 vec3 vec3::unit_vector() {
   return vec3(x()/length(),y()/length(),z()/length());
 }

vec3 vec3::operator+(vec3 v) { return vec3(x()+v.x(),y()+v.y(),z()+v.z()); }
vec3 vec3::operator+=(vec3 v) { return vec3(x()+v.x(),y()+v.y(),z()+v.z()); }
vec3 vec3::operator-(vec3 v) { return vec3(x()-v.x(),y()-v.y(),z()-v.z()); }
float vec3::operator*(vec3 v) { return x()*v.x() + y()*v.y() + z()*v.z(); }
vec3 vec3::operator*(float q) { return vec3(x()*q,y()*q,z()*q); }
