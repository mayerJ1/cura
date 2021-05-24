#include "visualize.h"
#include <vtkPolygon.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkCellArray.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>

void visualize_points(std::vector<cura::Point3>& ps){
    vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> p=vtkSmartPointer<vtkPolyData>::New();
    size_t nums=ps.size();
    for (size_t i=0;i<nums;i++) {
        points->InsertNextPoint(ps[i].x, ps[i].y, ps[i].z);
    }
    p->SetPoints(points);

    std::cout<<p->GetNumberOfPoints();
//for point visualization, we need vtkVertexGlyphFilter
    auto vertexGraph=vtkSmartPointer<vtkVertexGlyphFilter>::New();
    vertexGraph->AddInputData(p);
    vertexGraph->Update();
    vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(vertexGraph->GetOutputPort());
    mapper->Update();
    vtkSmartPointer<vtkActor> actor =vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer =vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(.3, .6, .3); // Background color green

    renderWindow->Render();
    renderWindowInteractor->Start();
}

void visualize_slice_polygon_data(std::vector<cura::SlicerLayer>& sls, size_t index){

    cura::Polygons polys = sls[index].polygons;

    size_t I=polys.size();

    size_t J=polys[0].size();

    vtkSmartPointer<vtkNamedColors> colors=vtkSmartPointer<vtkNamedColors>::New();

    std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

    vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
    cura::coord_t z=0;
    points->SetNumberOfPoints(J+1);
    for (size_t i=0;i<J;++i) {
        points->SetPoint(i, polys[0][i].X, polys[0][i].Y, z);
    }
    points->SetPoint(J, polys[0][0].X,polys[0][0].Y,0);

     vtkSmartPointer<vtkCellArray> lines=vtkSmartPointer<vtkCellArray>::New();
     lines->InsertNextCell(static_cast<size_t>(J+1));
     for (size_t i=0;i<J;++i) {
         lines->InsertCellPoint(i);
     }
     lines->InsertCellPoint(0);

     vtkSmartPointer<vtkPolyData> polygon=vtkSmartPointer<vtkPolyData>::New();
     polygon->SetPoints(points);
     polygon->SetLines(lines);

     vtkSmartPointer<vtkPolyDataMapper> polygonMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
     polygonMapper->SetInputData(polygon);
     polygonMapper->Update();

     vtkSmartPointer<vtkActor> polygonActor=vtkSmartPointer<vtkActor>::New();
     polygonActor->SetMapper(polygonMapper);
     polygonActor->GetProperty();


     vtkSmartPointer<vtkRenderer> ren=vtkSmartPointer<vtkRenderer>::New();
     ren->AddActor(polygonActor);
     ren->SetBackground(colors->GetColor3d("BkgColor").GetData());

    ren->ResetCamera();

    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->SetWindowName("OrderedPolyLine");
    renWin->AddRenderer(ren);
    renWin->SetSize(300, 300);

    vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    renWin->Render();
    iren->Initialize();
    iren->Start();

}

//void visualize_full_slicer(std::vector<cura::SlicerLayer>& sls,std::vector<cura::Point3>& ps)
//{
//    vtkSmartPointer<vtkNamedColors> colors=vtkSmartPointer<vtkNamedColors>::New();
//    std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
//    colors->SetColor("BkgColor", bkg.data());
//    size_t num_point=ps.size();

//    size_t I=sls.size();
//    vtkSmartPointer<vtkPolyData> cells=vtkSmartPointer<vtkPolyData>::New();



//     vtkSmartPointer<vtkCellArray> lines=vtkSmartPointer<vtkCellArray>::New();
//     lines->InsertNextCell(static_cast<size_t>(J+1));
//     lines->InsertCellPoint(0);
//    for (size_t i=0;i<I;i++) {
//        size_t J=sls[i].polygons.size();
//        for (size_t j=0;j<J;j++) {
//            size_t K=sls[i].polygons[j].size();
//            vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
//            vtkSmartPointer<vtkCellArray> poly=vtkSmartPointer<vtkCellArray>::New();
//            poly->InsertNextCell(K);
//            points->SetNumberOfPoints(J+1);
//            for (size_t k=0;k<K;k++) {
//                points->SetPoint(i, polys[0][i].X, polys[0][i].Y, z);
//                poly->InsertCellPoint(i);
//            }
//            cells->SetLines(poly);
//        }

//    }


//    vtkSmartPointer<vtkPolyDataMapper> polygonMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
//    polygonMapper->SetInputData(cells);
//    polygonMapper->Update();

//    vtkSmartPointer<vtkActor> polygonActor=vtkSmartPointer<vtkActor>::New();
//    polygonActor->SetMapper(polygonMapper);
//    polygonActor->GetProperty();


//    vtkSmartPointer<vtkRenderer> ren=vtkSmartPointer<vtkRenderer>::New();
//    ren->AddActor(polygonActor);
//    ren->SetBackground(colors->GetColor3d("BkgColor").GetData());

//   ren->ResetCamera();

//   vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
//   renWin->SetWindowName("OrderedPolyLine");
//   renWin->AddRenderer(ren);
//   renWin->SetSize(600, 600);

//   vtkSmartPointer<vtkRenderWindowInteractor> iren=vtkSmartPointer<vtkRenderWindowInteractor>::New();
//   iren->SetRenderWindow(renWin);
//   renWin->Render();
//   iren->Initialize();
//   iren->Start();

//}
