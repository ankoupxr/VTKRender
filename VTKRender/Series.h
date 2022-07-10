#pragma once

#include <set>
#include <string>
#include <vector>
#include "Image.h"
 


namespace VTKRender
{
	class Series
	{
	public:
		Series();
		~Series();


	public:
		std::string Manufacturer;					//������
		std::string StationName;					//��������
		std::string SeriseNumber;					//
		std::string NumberOfSeriesRelatedInstances;	//
		std::vector<Image*> ImageList;			//��Series�е�ͼƬ�洢���������
	};
}

