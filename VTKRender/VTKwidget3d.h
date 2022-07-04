#pragma once

#include "VTKwidgetBase.h"


namespace VTKRender 
{
	class VTKwidget3d final : public VTKwidgetBase
	{
		public:
			VTKwidget3d() { InitWidget(); }
			~VTKwidget3d() = default;




		private: 

			vtkSmartPointer<vtkWidget3DInteractorStyle>

			void InitWidget();
			void InitBoxWidget();
	};
}

