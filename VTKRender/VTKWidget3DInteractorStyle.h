#pragma once

#include <vtkInteractorStyleTrackballCamera.h>

//3D½»»»Æ÷·â×°
namespace VTKRender 
{
	class vtkWidget3D;

	class VTKWidget3DInteractorStyle final : public vtkInteractorStyleTrackballCamera
	{
		public:
			static VTKWidget3DInteractorStyle* New();
			VTKWidget3DInteractorStyle() = default;
			~VTKWidget3DInteractorStyle() = default;
			//getters
			vtkWidget3D* getWidget() const { return  vtkwidget3D; }
			//TransferFunction* getTransferFunction() const { return m_transferFunction; }

			//setters
			void setWidget(vtkWidget3D* t_widget) { vtkwidget3D = t_widget; }
			//void setTransferFunction(TransferFunction* t_function) { m_transferFunction = t_function; }

	protected:
		void OnMouseMove() override;

	private:
		vtkWidget3D* vtkwidget3D = {};
		//TransferFunction* vtktransferFunction = {};
	};
}

