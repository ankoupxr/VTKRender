#pragma once
#include "VTKwidgetBase.h"

namespace VTKRender 
{
	class VTKwidget2d final : public VTKwidgetBase
	{
		public:
			VTKwidget2d() = default;
			~VTKwidget2d() = default;

			vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() const { return Interactor; }

		private:
			vtkSmartPointer<vtkRenderWindowInteractor> Interactor = {};
	};
}

