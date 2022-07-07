#pragma once

#include <QWidget>
#include <vtkStringArray.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkImageCast.h>

namespace VTKRender {
	class Reconstruction3d : public QWidget
	{
		Q_OBJECT

	public:
		Reconstruction3d(QWidget* parent = Q_NULLPTR);//默认构造
		Reconstruction3d(std::vector<std::string>* filenames_v, QWidget* parent = Q_NULLPTR);//带数据构造
		~Reconstruction3d();

		void OnReconstruction();

	private:
		vtkRenderer* m_Rec3dRenderer;
		vtkRenderWindow* m_Rec3dRenderWindow;
		vtkImageCast* m_ImageCast;
		vtkPiecewiseFunction* m_PiecewiseFunction;
		vtkColorTransferFunction* m_colorTransferFunction;
		vtkVolumeProperty* m_volumeProperty;
		//vtkVolumeRayCastCompositeFunction* m_VolumeRayCastCompositeFunction;
		vtkFixedPointVolumeRayCastMapper* m_FixedPointVolumeRayCastMapper;
		vtkVolume* volume1;
		//vtkSmartPointer<vtkMyDICOMImageReader> m_MyDICOMImageReader;
		vtkSmartPointer<vtkInteractorStyleTrackballCamera> TrackballCamera;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
		vtkGPUVolumeRayCastMapper* m_volumeMapper_gpu;
	private:
		void RenderPipeline_CPU(vtkStringArray*);//CPU渲染管线
		void RenderPipeline_GPU(vtkStringArray*);//GPU渲染管线
	};
}

