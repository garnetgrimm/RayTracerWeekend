#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include "meshbuild.h"
#include "math.h"

#define PI 3.14159265

using namespace std;

float max_color = 255;

vec3 color(ray r) {
  vec3 unit_direction = r.direction().unit_vector();
  float  t = (0.5)*(unit_direction.y() + 1.0);
  return vec3()*float(1.0-t) + vec3(0.5,0.7,1.0)*t;
}

bool intersect(face f, ray r) {

  vec3 faceEq = f.equation();
  vec3 rayEqt = r.equation();
  vec3 rayEq =  r.origin();

  float t = (f.equation().equals-(faceEq*rayEq))/(faceEq*rayEqt);
  //cout << faceEq << " " << rayEqt << " " << rayEq << " " << t << endl;

  //vec3 pt = r.point(t);
  vec3 pt=r.equation()*t;

  int posx = 0;
  int posy = 0;
  int posz = 0;

  float tolerance = 0.2;

  for(int i = 0; i < f.points().size(); i++) {
    if(pt.x()-f.points().at(i).x() > tolerance) {
      posx += 1;
    } else if(pt.x()-f.points().at(i).x() < -tolerance) {
      posx -= 1;
    }
    if(pt.y()-f.points().at(i).y() > tolerance) {
      posy += 1;
    } else if(pt.y()-f.points().at(i).y() < -tolerance) {
      posy -= 1;
    }
    //cout << pt.z() << " " << f.points().at(i).z() << endl;
    if(pt.z()-f.points().at(i).z() > tolerance) {
      posz += 1;
    } else if(pt.z()-f.points().at(i).z() < -tolerance) {
      posz -= 1;
    }
  }

  bool hit = true;
  if(isinf(t) || t < 0) hit = false;
  if(posx != 0) hit = false;
  if(posy != 0) hit = false;
  if(posz != 0) hit = false;

  if(!hit) {
    cout << f.equation() << " " << r.equation() << " " << " (" << t << ") " << endl;
    for(int i = 0; i < f.points().size(); i++) {
      cout << f.points().at(i) << endl;
    }
    cout << "!!!" << posx << " " << posy << " " << posz << "!!!" << "\n\n\n\n\n";
  }

  //if(hit) cout << "!!!" << posy << "!!!" << endl;

  return hit;
}

int main() {

  int fov=5;
  int max_y=30;
  int max_x=30;
  int cam_x=0;
  int cam_y=0;
  int cam_z=0.5;
  int x_rotT=0;
  int y_rotT=0;
  int z_rotT=0;
  int img_size=10;

  for(int x = 0; x < 1; x++) {
  //cam_z-=1;
  //cam_y+=1;
  //fov+=1;
  float xRotx = cos(x_rotT*(3.14159265/180))*15;
  float xRoty = sin(x_rotT*(3.14159265/180))*15;
  x_rotT += 10;

  //fov+=1;
  //max_x+=5;
  //cam_y+=5;

  vec3 lower_left_corner = vec3(-(max_x/2)+cam_x,-(max_y/2)+cam_y,cam_z);
  //vec3 lower_left_corner = vec3(-(max_x/2)+xRotx,-(max_y/2),cam_z+xRoty);
  vec3 origin = vec3(0,0,0);
  vec3 horizontal = vec3(max_x,0,0);
  vec3 vertical = vec3(0,max_y,0);
  std::vector<face> faces = parse_obj("s(shift).obj");

  ofstream img("output" + std::to_string(x) + ".ppm");
  if(img.is_open()) {
    //cout << "Successfully opened image for writing\n";
    int nx = img_size;
    int ny = img_size;
    img << "P3\n" << nx << " " << ny << "\n" << max_color << "\n";
    for(int j = ny-1; j >= 0; j--) {
      for(int i = 0; i < nx; i++) {
          float u = float(i) / float(nx);
          float v = float(j) / float(ny);

          vec3 direction = lower_left_corner + (horizontal*u) + (vertical*v);

          ray r = ray(origin, direction);

          bool hit = false;
          for(int i = 0; i < faces.size(); i++) {
            if(intersect(faces.at(i), r)) hit = true;
          }

          //bool hit = false;
          //if(intersect(faces.at(1), r)) hit = true;
          //if(intersect(faces.at(2), r)) hit = true;
          //if(intersect(faces.at(3), r)) hit = true;
          //if(intersect(faces.at(4), r)) hit = true;
          //if(intersect(faces.at(5), r)) hit = true;
          //if(intersect(faces.at(0), r)) hit = true;

          int ir = 0;
          int ig = 0;
          int ib = 0;

          if(!hit) {
            ir = int(u*max_color);
            ig = int(v*max_color);
            //ib = int(direction.z()*max_color);
          }
          img << ir << " " << ig << " " << ib << "\n";
      }
      img << "\n";
    }
    //cout << "Image write complete\n";
  } else {
    cout << "Error: could not open file";
  }

  vec3 v1 = vec3(1,2,3);
  vec3 v2 = vec3(4,5,6);
  ray R1 = ray(v1,v2);
  }

}
