#include "VTKWidget3DInteractorStyle.h"
#include <vtkObjectFactory.h>
#include <vtkRenderWindowInteractor.h>


void VTKRender::VTKWidget3DInteractorStyle::OnMouseMove()
{
	auto* const CurrentEventPosition = Interactor->GetEventPosition();
	auto* const LastEventPosition = Interactor->GetLastEventPosition();

	if (State == VTKIS_SPIN)
	{
		return;
	}
	vtkInteractorStyleTrackballCamera::OnMouseMove();
}