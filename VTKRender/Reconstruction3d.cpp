#include "Reconstruction3d.h"
#include <vtkDecimatePro.h>
#include "vtkPiecewiseFunction.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageAppend.h>
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include <vtkDICOMImageReader.h>

VTKRender::Reconstruction3d::Reconstruction3d(QWidget *parent) : QWidget(parent)
{
	
}


VTKRender::Reconstruction3d::Reconstruction3d(std::vector<std::string>* filenames_v, QWidget* parent)
{
	m_Filenames = vtkSmartPointer<vtkStringArray>::New();
	for (int i = 0; i < filenames_v->size(); i++)
	{
		m_Filenames->InsertNextValue(filenames_v->at(i));
	}
	setWindowTitle(QStringLiteral("��ά�ؽ�-���ڽ���..."));
}


void VTKRender::Reconstruction3d::OnReconstruction()
{
	//RenderPipeline_GPU(m_Filenames);
	RenderPipeline_CPU(m_Filenames);
}


/*
CPU��Ⱦ
*/
void VTKRender::Reconstruction3d::RenderPipeline_CPU(vtkStringArray* _TargetFiles)
{
	m_Rec3dRenderer = vtkRenderer::New();//���û��ƶ���ָ��
	m_Rec3dRenderWindow = vtkRenderWindow::New();//���û��ƴ���
	m_Rec3dRenderWindow->AddRenderer(m_Rec3dRenderer);

	//�Ž�ȥQt

	renderWindowInteractor = vtkRenderWindowInteractor::New();//���û��ƽ�����������
	renderWindowInteractor->SetRenderWindow(m_Rec3dRenderWindow);//�����ƴ�����ӵ���������

	vtkDecimatePro* deci = vtkDecimatePro::New();//�������ݶ�ȡ��
	deci->SetTargetReduction(0.3);

	TrackballCamera = vtkInteractorStyleTrackballCamera::New();//�������
	renderWindowInteractor->SetInteractorStyle(TrackballCamera);

	//���ö�ȡDICOM
	m_DICOMImageReader = vtkSmartPointer<VTKwidgetDICOM>::New();
	m_DICOMImageReader->SetFileNames(_TargetFiles);

	m_DICOMImageReader->SetFileDimensionality(3);//������ʾͼ��ά��
	m_DICOMImageReader->SetDataScalarType(VTK_UNSIGNED_SHORT);
	m_DICOMImageReader->SetDataExtent(0, 255, 0, 255, 0, 62);//ͼƬ����ͼƬ����256x256�������������ʾ��124��ͼ
	m_DICOMImageReader->SetDataSpacing(0.9, 0.9, 0.9);//�������ؼ���

	m_ImageCast = vtkImageCast::New(); //��������ת��
	m_ImageCast->SetInputConnection(m_DICOMImageReader->GetOutputPort());

	//���ò�͸����
	m_PiecewiseFunction = vtkPiecewiseFunction::New();
	m_PiecewiseFunction->AddPoint(20, 0.0);
	m_PiecewiseFunction->AddPoint(255, 0.2);
	//������ɫ
	m_colorTransferFunction = vtkColorTransferFunction::New();
	m_colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);        //���ɫ�ʵ㣨��һ������������
	m_colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
	m_colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
	m_colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
	m_colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);
	//��������Ⱦ����
	m_volumeProperty = vtkVolumeProperty::New();					 //�趨һ���������������
	m_volumeProperty->SetColor(m_colorTransferFunction);             //������ɫ
	m_volumeProperty->SetScalarOpacity(m_PiecewiseFunction);		 //��͸����
	m_volumeProperty->ShadeOn();                                     //Ӱ��
	m_volumeProperty->SetInterpolationTypeToLinear();                //ֱ����������ֵ֮���𷢺���
	m_volumeProperty->SetAmbient(0.2);                               //������ϵ��
	m_volumeProperty->SetDiffuse(0.9);                               //������
	m_volumeProperty->SetSpecular(0.2);                              //�߹�ϵ��
	m_volumeProperty->SetSpecularPower(10);                          //�߹�ǿ�� 
	//�������
	m_FixedPointVolumeRayCastMapper = vtkFixedPointVolumeRayCastMapper::New();   //�������
	m_FixedPointVolumeRayCastMapper->SetInputConnection(m_ImageCast->GetOutputPort());     //ͼ����������
	m_FixedPointVolumeRayCastMapper->SetNumberOfThreads(3);
	//��ʾ͸ʾͼ�е�һ����ά����
	volume1 = vtkVolume::New();
	volume1->SetMapper(m_volumeMapper_gpu);
	volume1->SetProperty(m_volumeProperty);

	m_Rec3dRenderer->AddVolume(volume1);//�����������
	renderWindowInteractor->Initialize();
	this->setWindowTitle(QStringLiteral("��ά�ؽ�-CPU�������"));
	renderWindowInteractor->Start();								//��ʼ�������н�������
	m_Rec3dRenderer->ResetCameraClippingRange();

	m_Rec3dRenderer->Render();
}


void VTKRender::Reconstruction3d::RenderPipeline_GPU(vtkStringArray* _TargetFiles)
{
	m_Rec3dRenderer = vtkRenderer::New();
	m_Rec3dRenderWindow = vtkRenderWindow::New();
	m_Rec3dRenderWindow->AddRenderer(m_Rec3dRenderer);
	//Qt
	renderWindowInteractor = vtkRenderWindowInteractor::New();		  //���û��ƽ����������ڵ�
	renderWindowInteractor->SetRenderWindow(m_Rec3dRenderWindow);//�����ƴ�����ӵ���������

	vtkDecimatePro* deci = vtkDecimatePro::New();					
	deci->SetTargetReduction(0.3);

	TrackballCamera = vtkInteractorStyleTrackballCamera::New();       //����ģʽ:����������������       
	renderWindowInteractor->SetInteractorStyle(TrackballCamera);

	//���ö�ȡDICOM
	m_DICOMImageReader = vtkSmartPointer<VTKwidgetDICOM>::New();
	m_DICOMImageReader->SetFileNames(_TargetFiles);

	m_DICOMImageReader->SetFileDimensionality(3);//������ʾͼ��ά��
	m_DICOMImageReader->SetDataScalarType(VTK_UNSIGNED_SHORT);
	m_DICOMImageReader->SetDataExtent(0, 255, 0, 255, 0, 62);//ͼƬ����ͼƬ����256x256�������������ʾ��124��ͼ
	m_DICOMImageReader->SetDataSpacing(0.9, 0.9, 0.9);//�������ؼ���

	m_ImageCast = vtkImageCast::New(); //��������ת��
	m_ImageCast->SetInputConnection(m_DICOMImageReader->GetOutputPort());

	//���ò�͸����
	m_PiecewiseFunction = vtkPiecewiseFunction::New();
	m_PiecewiseFunction->AddPoint(20, 0.0);
	m_PiecewiseFunction->AddPoint(255, 0.2);
	//������ɫ
	m_colorTransferFunction = vtkColorTransferFunction::New();
	m_colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);        //���ɫ�ʵ㣨��һ������������
	m_colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
	m_colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
	m_colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
	m_colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);
	//��������Ⱦ����
	m_volumeProperty = vtkVolumeProperty::New();					 //�趨һ���������������
	m_volumeProperty->SetColor(m_colorTransferFunction);             //������ɫ
	m_volumeProperty->SetScalarOpacity(m_PiecewiseFunction);		 //��͸����
	m_volumeProperty->ShadeOn();                                     //Ӱ��
	m_volumeProperty->SetInterpolationTypeToLinear();                //ֱ����������ֵ֮���𷢺���
	m_volumeProperty->SetAmbient(0.2);                               //������ϵ��
	m_volumeProperty->SetDiffuse(0.9);                               //������
	m_volumeProperty->SetSpecular(0.2);                              //�߹�ϵ��
	m_volumeProperty->SetSpecularPower(10);                          //�߹�ǿ�� 
	//�������
	m_FixedPointVolumeRayCastMapper = vtkFixedPointVolumeRayCastMapper::New();   //�������
	m_FixedPointVolumeRayCastMapper->SetInputConnection(m_ImageCast->GetOutputPort());     //ͼ����������
	m_FixedPointVolumeRayCastMapper->SetNumberOfThreads(3);
	//��ʾ͸ʾͼ�е�һ����ά����
	volume1 = vtkVolume::New();
	volume1->SetMapper(m_volumeMapper_gpu);
	volume1->SetProperty(m_volumeProperty);

	m_Rec3dRenderer->AddVolume(volume1);//�����������
	renderWindowInteractor->Initialize();
	this->setWindowTitle(QStringLiteral("��ά�ؽ�-CPU�������"));
	renderWindowInteractor->Start();								//��ʼ�������н�������
	m_Rec3dRenderer->ResetCameraClippingRange();

	m_Rec3dRenderer->Render();
}