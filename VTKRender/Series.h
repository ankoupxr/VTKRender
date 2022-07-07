#pragma once

#include <set>
#include <memory>
#include "Image.h"
 


namespace VTKRender
{
	class Series
	{
	public:
		Series() = default;
		~Series() = default;



		//setters

	private:
		std::string Manufacturer;					//������
		std::string StationName;					//��������
		std::string SeriseNumber;					//
		std::string NumberOfSeriesRelatedInstances;	//
		std::vector<Image*> ImageList;			//��Series�е�ͼƬ�洢���������
	};
}

