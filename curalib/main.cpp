//Copyright (c) 2018 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#include <iostream> //To change the formatting of std::cerr.
#include <signal.h> //For floating point exceptions.

#include "mesh.h"
#include "MeshGroup.h"
#include "slicer.h"
#include "sliceProcess.h"
#include "visualize.h"

void show_model()
{
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    const char *path = "/home/mjh/curaengine/src/3DR_Spool_V2_001_RTP.stl";

    vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(path);
    reader->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderer->SetBackground(.2, .2, .2);
    renderer->ResetCameraClippingRange();

    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

}

int main(int argc, char **argv) {
    const char *f = "/home/mjh/curaengine/src/3DR_Spool_V2_001_RTP.stl";
    cura::slicerProcess s(f);
    s.has_z();
    s.compute();
    s.get_points();
//    show_model();
//    visualize_points(s.points);
    visualize_slice_polygon_data(s.layers, 60);
//    visualize_full_slicer(s.layers,s.points);



    return 0;
}
