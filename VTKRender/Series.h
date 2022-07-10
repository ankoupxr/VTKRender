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
		std::string Manufacturer;					//制造商
		std::string StationName;					//仪器名称
		std::string SeriseNumber;					//
		std::string NumberOfSeriesRelatedInstances;	//
		std::vector<Image*> ImageList;			//该Series中的图片存储在这个表里
	};
}

