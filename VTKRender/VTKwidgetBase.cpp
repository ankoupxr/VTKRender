#include "VTKwidgetBase.h"



void VTKRender::VTKwidgetBase::setRenderWindowsMPR
(const vtkSmartPointer<vtkRenderWindow>& t_sagittal, 
	const vtkSmartPointer<vtkRenderWindow>& t_coronal, const vtkSmartPointer<vtkRenderWindow>& t_axial)
{
	RenderWindows[0] = t_sagittal;
	RenderWindows[1] = t_coronal;
	RenderWindows[2] = t_axial;
}
