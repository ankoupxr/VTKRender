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
		static void setStyle(const QString& style);//加载属性表
		static bool isADicomOrDicomDir(std::string filename);//用于判断一个文件是否为遵循Dicom3.0标准的图片文件或Dir文件
	};
}