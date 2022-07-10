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
	setWindowTitle(QStringLiteral("三维重建-正在解算..."));
}


void VTKRender::Reconstruction3d::OnReconstruction()
{
	//RenderPipeline_GPU(m_Filenames);
	RenderPipeline_CPU(m_Filenames);
}


/*
CPU渲染
*/
void VTKRender::Reconstruction3d::RenderPipeline_CPU(vtkStringArray* _TargetFiles)
{
	m_Rec3dRenderer = vtkRenderer::New();//设置绘制对象指针
	m_Rec3dRenderWindow = vtkRenderWindow::New();//设置绘制窗口
	m_Rec3dRenderWindow->AddRenderer(m_Rec3dRenderer);

	//放进去Qt

	renderWindowInteractor = vtkRenderWindowInteractor::New();//设置绘制交互操作窗口
	renderWindowInteractor->SetRenderWindow(m_Rec3dRenderWindow);//将绘制窗口添加到交互窗口

	vtkDecimatePro* deci = vtkDecimatePro::New();//减少数据读取点
	deci->SetTargetReduction(0.3);

	TrackballCamera = vtkInteractorStyleTrackballCamera::New();//交互相机
	renderWindowInteractor->SetInteractorStyle(TrackballCamera);

	//设置读取DICOM
	m_DICOMImageReader = vtkSmartPointer<VTKwidgetDICOM>::New();
	m_DICOMImageReader->SetFileNames(_TargetFiles);

	m_DICOMImageReader->SetFileDimensionality(3);//设置显示图像维度
	m_DICOMImageReader->SetDataScalarType(VTK_UNSIGNED_SHORT);
	m_DICOMImageReader->SetDataExtent(0, 255, 0, 255, 0, 62);//图片属性图片像素256x256，最后两参数表示有124张图
	m_DICOMImageReader->SetDataSpacing(0.9, 0.9, 0.9);//设置像素间间距

	m_ImageCast = vtkImageCast::New(); //数据类型转换
	m_ImageCast->SetInputConnection(m_DICOMImageReader->GetOutputPort());

	//设置不透明度
	m_PiecewiseFunction = vtkPiecewiseFunction::New();
	m_PiecewiseFunction->AddPoint(20, 0.0);
	m_PiecewiseFunction->AddPoint(255, 0.2);
	//设置颜色
	m_colorTransferFunction = vtkColorTransferFunction::New();
	m_colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);        //添加色彩点（第一个参数索引）
	m_colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
	m_colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
	m_colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
	m_colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);
	//设置体渲染属性
	m_volumeProperty = vtkVolumeProperty::New();					 //设定一个体绘容器的属性
	m_volumeProperty->SetColor(m_colorTransferFunction);             //设置颜色
	m_volumeProperty->SetScalarOpacity(m_PiecewiseFunction);		 //不透明度
	m_volumeProperty->ShadeOn();                                     //影阴
	m_volumeProperty->SetInterpolationTypeToLinear();                //直线与样条插值之间逐发函数
	m_volumeProperty->SetAmbient(0.2);                               //环境光系数
	m_volumeProperty->SetDiffuse(0.9);                               //漫反射
	m_volumeProperty->SetSpecular(0.2);                              //高光系数
	m_volumeProperty->SetSpecularPower(10);                          //高光强度 
	//体绘制器
	m_FixedPointVolumeRayCastMapper = vtkFixedPointVolumeRayCastMapper::New();   //体绘制器
	m_FixedPointVolumeRayCastMapper->SetInputConnection(m_ImageCast->GetOutputPort());     //图像数据输入
	m_FixedPointVolumeRayCastMapper->SetNumberOfThreads(3);
	//表示透示图中的一组三维数据
	volume1 = vtkVolume::New();
	volume1->SetMapper(m_volumeMapper_gpu);
	volume1->SetProperty(m_volumeProperty);

	m_Rec3dRenderer->AddVolume(volume1);//放入绘制类中
	renderWindowInteractor->Initialize();
	this->setWindowTitle(QStringLiteral("三维重建-CPU解算完成"));
	renderWindowInteractor->Start();								//初始化并进行交互绘制
	m_Rec3dRenderer->ResetCameraClippingRange();

	m_Rec3dRenderer->Render();
}


void VTKRender::Reconstruction3d::RenderPipeline_GPU(vtkStringArray* _TargetFiles)
{
	m_Rec3dRenderer = vtkRenderer::New();
	m_Rec3dRenderWindow = vtkRenderWindow::New();
	m_Rec3dRenderWindow->AddRenderer(m_Rec3dRenderer);
	//Qt
	renderWindowInteractor = vtkRenderWindowInteractor::New();		  //设置绘制交互操作窗口的
	renderWindowInteractor->SetRenderWindow(m_Rec3dRenderWindow);//将绘制窗口添加到交互窗口

	vtkDecimatePro* deci = vtkDecimatePro::New();					
	deci->SetTargetReduction(0.3);

	TrackballCamera = vtkInteractorStyleTrackballCamera::New();       //交互模式:左键控制摄像机环绕       
	renderWindowInteractor->SetInteractorStyle(TrackballCamera);

	//设置读取DICOM
	m_DICOMImageReader = vtkSmartPointer<VTKwidgetDICOM>::New();
	m_DICOMImageReader->SetFileNames(_TargetFiles);

	m_DICOMImageReader->SetFileDimensionality(3);//设置显示图像维度
	m_DICOMImageReader->SetDataScalarType(VTK_UNSIGNED_SHORT);
	m_DICOMImageReader->SetDataExtent(0, 255, 0, 255, 0, 62);//图片属性图片像素256x256，最后两参数表示有124张图
	m_DICOMImageReader->SetDataSpacing(0.9, 0.9, 0.9);//设置像素间间距

	m_ImageCast = vtkImageCast::New(); //数据类型转换
	m_ImageCast->SetInputConnection(m_DICOMImageReader->GetOutputPort());

	//设置不透明度
	m_PiecewiseFunction = vtkPiecewiseFunction::New();
	m_PiecewiseFunction->AddPoint(20, 0.0);
	m_PiecewiseFunction->AddPoint(255, 0.2);
	//设置颜色
	m_colorTransferFunction = vtkColorTransferFunction::New();
	m_colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);        //添加色彩点（第一个参数索引）
	m_colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
	m_colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
	m_colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
	m_colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);
	//设置体渲染属性
	m_volumeProperty = vtkVolumeProperty::New();					 //设定一个体绘容器的属性
	m_volumeProperty->SetColor(m_colorTransferFunction);             //设置颜色
	m_volumeProperty->SetScalarOpacity(m_PiecewiseFunction);		 //不透明度
	m_volumeProperty->ShadeOn();                                     //影阴
	m_volumeProperty->SetInterpolationTypeToLinear();                //直线与样条插值之间逐发函数
	m_volumeProperty->SetAmbient(0.2);                               //环境光系数
	m_volumeProperty->SetDiffuse(0.9);                               //漫反射
	m_volumeProperty->SetSpecular(0.2);                              //高光系数
	m_volumeProperty->SetSpecularPower(10);                          //高光强度 
	//体绘制器
	m_FixedPointVolumeRayCastMapper = vtkFixedPointVolumeRayCastMapper::New();   //体绘制器
	m_FixedPointVolumeRayCastMapper->SetInputConnection(m_ImageCast->GetOutputPort());     //图像数据输入
	m_FixedPointVolumeRayCastMapper->SetNumberOfThreads(3);
	//表示透示图中的一组三维数据
	volume1 = vtkVolume::New();
	volume1->SetMapper(m_volumeMapper_gpu);
	volume1->SetProperty(m_volumeProperty);

	m_Rec3dRenderer->AddVolume(volume1);//放入绘制类中
	renderWindowInteractor->Initialize();
	this->setWindowTitle(QStringLiteral("三维重建-CPU解算完成"));
	renderWindowInteractor->Start();								//初始化并进行交互绘制
	m_Rec3dRenderer->ResetCameraClippingRange();

	m_Rec3dRenderer->Render();
}