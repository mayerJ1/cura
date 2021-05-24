#ifndef SLICEPROCESS_H
#define SLICEPROCESS_H
#include "mesh.h"
#include "MeshGroup.h"
#include "slicer.h"
#include "FMatrix4x3.h"
#include "polygon.h"
#include "string.h"
#include "utils/FMatrix4x3.h"

namespace cura{
class slicerProcess {
public:
  slicerProcess(const char* filename);
  
  ~slicerProcess() {}
  std::vector<SlicerLayer> layers;

  void load_stl_file();
//for visulazation
  void has_z();
  void compute();
//for visulazation
  void get_points();
  Mesh mesh;
  std::vector<coord_t> z_values;
  const char* filename;
  bool has_zvalue=false;
  FMatrix4x3 matrix;
  std::vector<cura::Point3> points;
};

}


#endif
