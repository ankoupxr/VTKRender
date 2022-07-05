#pragma once

#include <vtkInteractorStyleImage.h>
#include "VTKwidget2d.h"

namespace VTKRender 
{
	class VTKwidget2DInteractorStyle final : public vtkInteractorStyleImage
	{
	public:
		static VTKwidget2DInteractorStyle* New();
		
		VTKwidget2DInteractorStyle() = default;
		~VTKwidget2DInteractorStyle() = default;

		int getCurrentImageIndex() const { return currentImageIndex; }

	protected:
		void OnMouseMove() override;
		void OnMouseWheelForward() override;
		void OnMouseWheelBackward() override;
		void OnLeftButtonDown() override;
		void OnLeftButtonUp() override;
		void OnRightButtonDown() override;
		void OnRightButtonUp() override;
		void OnMiddleButtonDown() override;
		void OnMiddleButtonUp() override;
		void Dolly() override;

	private:
		VTKwidget2d* widget2D = {};
		int currentImageIndex = {};

		void refreshImage() const;
		void updateOverlayWindowLevelApply() const;
		void updateOverlayHUValue() const;
	};
}

