#pragma once
#include <QString>
#include <QFileDialog>
#include <qapplication.h>

namespace VTKRender 
{
	class CommonHelper
	{
	public:
		CommonHelper();
		~CommonHelper();
		static void setStyle(const QString& style);//�������Ա�
		static bool isADicomOrDicomDir(std::string filename);//�����ж�һ���ļ��Ƿ�Ϊ��ѭDicom3.0��׼��ͼƬ�ļ���Dir�ļ�
	};
}