#pragma once
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

namespace VTKRender
{
	class VTKwidgetBase
	{
		public:
			VTKwidgetBase() = default;
			virtual ~VTKwidgetBase() = default;

			vtkSmartPointer<vtkRenderWindow>* getRenderWindows() { return RenderWindows; }
			void setRenderWindow(const vtkSmartPointer<vtkRenderWindow>& t_renderWindow) { RenderWindows[0] = t_renderWindow; }
			void setRenderWindowsMPR(const vtkSmartPointer<vtkRenderWindow>& t_sagittal,
				const vtkSmartPointer<vtkRenderWindow>& t_coronal,
				const vtkSmartPointer<vtkRenderWindow>& t_axial);
			virtual void setInteractor(const vtkSmartPointer<vtkRenderWindowInteractor>& t_interactor) = 0;

			virtual void render() = 0;

	protected:
		vtkSmartPointer<vtkRenderWindow> RenderWindows[3] = {};
		vtkRenderWindow* ActiveRenderWindow = nullptr;
	};
}

