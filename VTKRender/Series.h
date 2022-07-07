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
		std::string Manufacturer;					//制造商
		std::string StationName;					//仪器名称
		std::string SeriseNumber;					//
		std::string NumberOfSeriesRelatedInstances;	//
		std::vector<Image*> ImageList;			//该Series中的图片存储在这个表里
	};
}

