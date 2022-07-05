#include "VTKwidget2DInteractorStyle.h"
#include <vtkRenderWindowInteractor.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>

void VTKRender::VTKwidget2DInteractorStyle::OnMouseMove()
{
	switch (State)
	{
		case VTKIS_WINDOW_LEVEL:
			return;
		default:
			break;
	}
}