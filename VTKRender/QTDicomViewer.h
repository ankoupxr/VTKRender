#pragma once

//Qt
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QTimer>
//vtk
#include <vtkRenderWindow.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkAutoInit.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDICOMImageReader.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkDistanceWidget.h>
#include <vtkAngleWidget.h>
#include <vtkContourWidget.h>
#include <vtkOrientedGlyphContourRepresentation.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkBiDimensionalWidget.h>
#include <vtkImageCast.h>

#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkSmartPointer.h>  
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>  
#include <vtkGPUVolumeRayCastMapper.h>  
#include <vtkVolumeProperty.h>  
#include <vtkPiecewiseFunction.h>  
#include <vtkColorTransferFunction.h>  
#include <vtkVolume.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkCamera.h>
#include "vtkUnsignedCharArray.h"    
#include "vtkPiecewiseFunction.h"    
#include "vtkColorTransferFunction.h"       
#include "vtkImageData.h"       
#include "vtkRenderWindow.h"    
#include "vtkWin32OpenGLRenderWindow.h"  
#include "vtkInteractorStyleTrackballActor.h"  
#include "vtkImageChangeInformation.h"  
#include "vtkGPUVolumeRayCastMapper.h"  
#include "vtkGPUInfoList.h"  
#include "vtkGPUInfo.h"  
#include <vtkStructuredPoints.h>  
#include <vtkStructuredPointsReader.h>   
#include <vtkPiecewiseFunction.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkVolumeProperty.h>  
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <QComboBox>

#include "VTKwidgetDICOM.h"
#include "VTKwidget2DInteractorStyle.h"
#include "VTKBiDimensionalCallback.h"
#include "Patient.h"



namespace VTKRender
{

	class QTDicomViewer : public QMainWindow
	{
		Q_OBJECT

		public:
			QTDicomViewer(QWidget* parent = Q_NULLPTR);

			enum CURSOR
			{
				POINTRE,		//默认指针
				ZOOM,			//缩放
				GRAYLEVEL,		//灰阶
				PROTRACTOR,		//量角器
				RULER,			//测距尺
				CONTOUR,		//轮廓
				BIDI,			//二维尺
				MOVE			//移动
			}CursorType;
			enum WINDOWWL
			{
				Default,		//默认窗宽窗位
				All,			//全部动态范围
				Abdomen,		//腹部
				BloodVessel,	//血管
				Bones,			//骨骼
				Brain,			//脑
				Medias,			//纵膈
				Lungs			//肺
			}ImageWindow;
			enum STATE
			{
				Idel,			//空闲状态
				SingleImage,	//单张图片状态
				Folder,		//打开文件夹状态
				Dir,			//打开DICOMDIR状态
				Err,			//出现严重错误的状态
				Debug			//调试状态
			}AppState;
	private:
		//Ui::QvtkDicomViewerClass ui;
		vtkSmartPointer<vtkImageViewer2 > m_pImageViewer;
		vtkSmartPointer<vtkRenderer > m_pRenderder;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<vtkDICOMImageReader> reader;
		vtkSmartPointer<vtkActor2D> sliceTextActor;//必须是全局的.否则无法擦除上一次得到痕迹
		vtkSmartPointer<vtkActor2D> usageTextActor1;
		vtkSmartPointer<vtkActor2D> usageTextActor2;
		vtkSmartPointer<vtkActor2D> usageTextActor3;
		vtkSmartPointer<VTKwidget2DInteractorStyle> myInteractorStyle;
		vtkSmartPointer<vtkDistanceWidget> distanceWidget;//测距
		vtkSmartPointer<vtkAngleWidget> angleWidget;//测量角度
		vtkSmartPointer<vtkContourWidget> contourWidget;//轮廓选框
		vtkSmartPointer<vtkAxesActor> axes;
		vtkSmartPointer<vtkOrientedGlyphContourRepresentation> contourRepresentation;
		vtkSmartPointer<vtkOrientationMarkerWidget> widget;
		vtkSmartPointer<vtkBiDimensionalWidget> biDimensionalWidget;
		vtkSmartPointer<VTKBiDimensionalCallback> biDimensionalCallback;

		QIcon icon_Play;
		QIcon icon_Pause;
		bool PlayFlag;
		QTimer* m_pTimer;
		int min;
		int max;
		int current;

		QPoint PrePosition;					//前一次的右键点击位置
		QMenu* TreeViewMenu_OnEmpty;		//树右键菜单->树为空
		QMenu* TreeViewMenu_OnPatient;		//树右键菜单->病人节点
		QMenu* TreeViewMenu_OnSeries;		//树右键菜单->Series节点
		QMenu* TreeViewMenu_OnImage;		//树右键菜单->Image节点

		std::string Current_patientId;//当前的病人ID
		Patient* CurrentPatient;		//当前病人
		QModelIndex indexSelect;//树视图中
		DicomDirTreeModel* m_dicomdirtreemodel;

	};

}
