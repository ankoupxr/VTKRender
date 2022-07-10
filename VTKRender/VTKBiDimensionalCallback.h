#pragma once
#include "vtkCommand.h"
#include <vtkBiDimensionalWidget.h>
#include <vtkBiDimensionalRepresentation2D.h>

namespace VTKRender 
{
	class VTKBiDimensionalCallback : public vtkCommand
	{
	public:
		static VTKBiDimensionalCallback* New();

		virtual void Execute(vtkObject* caller, unsigned long, void*);
		VTKBiDimensionalCallback();
	};
}