#ifndef VISUALIZE_H
#define VISUALIZE_H
#include <vtkSTLReader.h>
#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <iostream>
#include <vtkVertexGlyphFilter.h>
#include <vector>
#include "sliceProcess.h"

//cura::slicerProcess s, ps=s.points
void visualize_points(std::vector<cura::Point3>& ps);

//polys is a SlicerLayer's polygons data, we can get the results of slice.
//cura::slicerProcess s, polys=s.layers
void visualize_slice_polygon_data(std::vector<cura::SlicerLayer>& sls, size_t index);

void visualize_full_slicer(std::vector<cura::SlicerLayer>& sls,std::vector<cura::Point3>& ps);
#endif
