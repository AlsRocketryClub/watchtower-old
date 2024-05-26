/*
-----------------------------------

VTK Plotter for visualizing the trajectory 

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include <iostream>
#include <vtkSmartPointer.h> 
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkLineSource.h>

// Main function
int main(int, char *[])
{
    // Create two points
    double p0[3] = {0.0, 0.0, 0.0};
    double p1[3] = {1.0, 1.0, 1.0};

    // Create a vtkLineSource
    vtkSmartPointer<vtkLineSource> lineSource = vtkSmartPointer<vtkLineSource>::New();
    lineSource->SetPoint1(p0);
    lineSource->SetPoint2(p1);
    lineSource->Update();

    return 0;
}

