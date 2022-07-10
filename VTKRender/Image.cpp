#include "Image.h"


namespace VTKRender 
{

	Image::Image()
	{
	}


	Image::~Image()
	{
	}
	std::string Image::getReferencedFileID()
	{
		return ReferencedFileID;
	}
	void Image::setReferencedFileID(std::string value)
	{
		ReferencedFileID = value;
	}
	std::string Image::getInstanceCreationDate()
	{
		return InstanceCreationDate;
	}
	void Image::setInstanceCreationDate(std::string value)
	{
		InstanceCreationDate = value;
	}
	std::string Image::getkpv()
	{
		return kpv;
	}
	void Image::setkpv(std::string value)
	{
		kpv = value;
	}
	std::string Image::getSliceLocation()
	{
		return SliceLocation;
	}
	void Image::setSliceLocation(std::string value)
	{
		SliceLocation = value;
	}
	std::string Image::getPixelSpacing()
	{
		return PixelSpacing;
	}
	void Image::setPixelSpacing(std::string value)
	{
		PixelSpacing = value;
	}
	int Image::getRow()
	{
		return row;
	}
	void Image::setRow(int value)
	{
		row = value;
	}
	int Image::getCol()
	{
		return col;
	}
	void Image::setCol(int value)
	{
		col = value;
	}
}