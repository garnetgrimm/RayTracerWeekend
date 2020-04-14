#include "meshbuild.h"
#include "ray.h"
#include "vec3.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::vector<vec3> verts;
std::vector<face> faces;

face::face(std::vector<vec3> points) {
  vs=points;
}

vec3 face::equation() {
  std::vector<vec3> vs = points();
  vec3 PQ = vs.at(0)-vs.at(1);
  vec3 PR = vs.at(0)-vs.at(2);
  vec3 c = PQ.cross(PR);
  vec3 ref = vs.at(0);
  float eq = (ref*c);
  return c.setEquals(eq);
}

std::vector<vec3> face::points() { return vs; }

std::vector<std::string> split(std::string s, char del) {
  std::replace( s.begin(), s.end(), del, ' ');
  std::string buf;                 // Have a buffer string
  std::stringstream ss(s);       // Insert the string into a stream
  std::vector<std::string> tokens; // Create vector to hold our words
  while (ss >> buf) tokens.push_back(buf);
  return  tokens;
}

vec3 parse_v(std::vector<std::string> sline) {
  return vec3(std::stof(sline[1]),std::stof(sline[2]),std::stof(sline[3]));
}

face parse_f(std::vector<std::string> sline) {
  std::vector<vec3> vs;
  for(int i = 1; i < sline.size(); i++) {
      std::vector<std::string> idxs = split(sline[i], '/');
      vec3 v = verts.at(std::stof(idxs[0])-1);
      vs.push_back(v);
  }
  face f = face(vs);
  return f;
}

std::vector<face> parse_obj(std::string filename) {
  ifstream file;
  file.open(filename);
  std::string line;
  if(file.is_open()) {
    //cout << "OBJ Opened Correctly" << endl;
    while(std::getline(file,line)) {
      std::vector<std::string> sline = split(line, ' ');
      if(sline[0] == "v") {
        verts.push_back(parse_v(sline));
      } else if(sline[0] == "f") {
        faces.push_back(parse_f(sline));
      }

    }
    //cout << "Properly read OBJ" << endl;
  }
  return faces;
}
