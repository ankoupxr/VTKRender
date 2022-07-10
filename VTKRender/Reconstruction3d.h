#pragma once

#include <QWidget>
#include <vtkStringArray.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkImageCast.h>
#include "VTKwidgetDICOM.h"

namespace VTKRender {
	class Reconstruction3d : public QWidget
	{
		Q_OBJECT

	public:
		Reconstruction3d(QWidget *parent = Q_NULLPTR);//Ĭ�Ϲ���
		Reconstruction3d(std::vector<std::string>* filenames_v, QWidget* parent = Q_NULLPTR);//�����ݹ���
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
		vtkSmartPointer<VTKwidgetDICOM> m_DICOMImageReader;
		vtkSmartPointer<vtkInteractorStyleTrackballCamera> TrackballCamera;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
		vtkGPUVolumeRayCastMapper* m_volumeMapper_gpu;
		vtkSmartPointer<vtkStringArray> m_Filenames;
	private:
		void RenderPipeline_CPU(vtkStringArray*);//CPU��Ⱦ����
		void RenderPipeline_GPU(vtkStringArray*);//GPU��Ⱦ����
	};
}

