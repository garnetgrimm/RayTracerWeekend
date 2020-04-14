#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"

using namespace std;

vec3 origin = vec3(0,0,0);
vec3 horizontal = vec3(4,0,0);
vec3 vertical = vec3(0,2,0);
vec3 lower_left_corner = vec3(-2,-1,-1.9);
float max_color = 255;
float viewing_dist = 100;

vec3 color(ray r) {
  vec3 unit_direction = r.direction().unit_vector();
  float  t = (0.5)*(unit_direction.y() + 1.0);
  return vec3()*float(1.0-t) + vec3(0.5,0.7,1.0)*t;
}

bool hit_sphere(vec3 center, float radius, ray r) {
  /*bool made_hit = false;
  for(int t = 0; t < viewing_dist; t++) {
    vec3 dist = r.point(t) - center;
    if(dist.length() < radius) {
      //cout << dist.length() << endl;
      made_hit = true;
      break;
    }
  }
  return made_hit;*/
  
}

int main() {
  ofstream img("output.ppm");
  if(img.is_open()) {
    cout << "Successfully opened image\n";
    int nx = 320;
    int ny = 320;
    img << "P3\n" << nx << " " << ny << "\n" << max_color << "\n";
    for(int j = 1; j < ny+1; j++) {
      for(int i = 1; i < nx+1; i++) {
          float u = float(i) / float(nx);
          float v = float(j) / float(ny);
          //NOTE: I didnt have to saw ray r = ray(...)???
          //ray r(origin, lower_left_corner + (horizontal*u) + (v*vertical));
          vec3 direction = lower_left_corner + (horizontal*u) + (vertical*v);

          ray r = ray(origin, direction);
          vec3 col = color(r);

          bool hit = hit_sphere(origin, 2, r);

          int ir = 0;
          int ig = 0;
          int ib = 0;

          if(!hit) {
            ir = int(col.x()*max_color);
            ig = int(col.y()*max_color);
            ib = int(col.z()*max_color);
          }
          img << ir << " " << ig << " " << ib << "\n";
      }
      img << "\n";
    }
    cout << "Image write complete\n";
  } else {
    cout << "Error: could not open file";
  }

  vec3 v1 = vec3(1,2,3);
  vec3 v2 = vec3(4,5,6);
  ray R1 = ray(v1,v2);

  for(int i = 0; i <= 100; i+=10) {
    cout << i << "% " << R1.point(float(i)/100) << endl;
  }
}
