#include "sliceProcess.h"
#include"iostream"
#include "MeshGroup.h"

namespace cura {

  slicerProcess::slicerProcess(const char* filename_){
      filename=filename_;
      load_stl_file();
  }
  void slicerProcess::load_stl_file() {
    int read_success;
    read_success=cura::loadMeshSTL_binary(&mesh, filename, matrix);
    if (read_success==1) {
        std::cout<<"read_successful"<<std::endl;
      }
}
  void slicerProcess::compute(){
      coord_t hight=mesh.max().z-mesh.min().z;
      const cura::coord_t thick=300;
      const size_t num_layer=hight/thick;
      Slicer slicer(&mesh, thick, num_layer);
      //std::cout<<mesh.max();
      layers=slicer.layers;
      for (int i=0;i<layers.size();++i) {
          layers[i].makePolygons();
      }
      if (has_zvalue){
          for (size_t i=0;i<num_layer;i++) {
              z_values.push_back(thick+i*thick);
          }
      }

  }

  void slicerProcess::has_z(){
      this->has_zvalue=true;
  }

  void slicerProcess::get_points(){
      for (size_t i=0; i<layers.size(); ++i) {
          for (size_t j=0; j<layers[i].polygons.size(); ++j) {
              for (size_t k=0; k<layers[i].polygons[j].size(); ++k ){
                  Point p=layers[i].polygons[j][k];
                  points.push_back(Point3(p.X,p.Y,z_values[i]));
              }
          }


      }
  }
}
