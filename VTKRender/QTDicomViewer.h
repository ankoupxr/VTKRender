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
				POINTRE,		//Ĭ��ָ��
				ZOOM,			//����
				GRAYLEVEL,		//�ҽ�
				PROTRACTOR,		//������
				RULER,			//����
				CONTOUR,		//����
				BIDI,			//��ά��
				MOVE			//�ƶ�
			}CursorType;
			enum WINDOWWL
			{
				Default,		//Ĭ�ϴ���λ
				All,			//ȫ����̬��Χ
				Abdomen,		//����
				BloodVessel,	//Ѫ��
				Bones,			//����
				Brain,			//��
				Medias,			//����
				Lungs			//��
			}ImageWindow;
			enum STATE
			{
				Idel,			//����״̬
				SingleImage,	//����ͼƬ״̬
				Folder,		//���ļ���״̬
				Dir,			//��DICOMDIR״̬
				Err,			//�������ش����״̬
				Debug			//����״̬
			}AppState;
	private:
		//Ui::QvtkDicomViewerClass ui;
		vtkSmartPointer<vtkImageViewer2 > m_pImageViewer;
		vtkSmartPointer<vtkRenderer > m_pRenderder;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<vtkDICOMImageReader> reader;
		vtkSmartPointer<vtkActor2D> sliceTextActor;//������ȫ�ֵ�.�����޷�������һ�εõ��ۼ�
		vtkSmartPointer<vtkActor2D> usageTextActor1;
		vtkSmartPointer<vtkActor2D> usageTextActor2;
		vtkSmartPointer<vtkActor2D> usageTextActor3;
		vtkSmartPointer<VTKwidget2DInteractorStyle> myInteractorStyle;
		vtkSmartPointer<vtkDistanceWidget> distanceWidget;//���
		vtkSmartPointer<vtkAngleWidget> angleWidget;//�����Ƕ�
		vtkSmartPointer<vtkContourWidget> contourWidget;//����ѡ��
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

		QPoint PrePosition;					//ǰһ�ε��Ҽ����λ��
		QMenu* TreeViewMenu_OnEmpty;		//���Ҽ��˵�->��Ϊ��
		QMenu* TreeViewMenu_OnPatient;		//���Ҽ��˵�->���˽ڵ�
		QMenu* TreeViewMenu_OnSeries;		//���Ҽ��˵�->Series�ڵ�
		QMenu* TreeViewMenu_OnImage;		//���Ҽ��˵�->Image�ڵ�

		std::string Current_patientId;//��ǰ�Ĳ���ID
		Patient* CurrentPatient;		//��ǰ����
		QModelIndex indexSelect;//����ͼ��
		DicomDirTreeModel* m_dicomdirtreemodel;

	};

}
