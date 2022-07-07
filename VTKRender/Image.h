#pragma once

#include <vtkDICOMImageReader.h>
#include <vtkWeakPointer.h>
#include <vtkSmartPointer.h>

namespace VTKRender
{

	class Image
	{
	public:
		Image() = default;
		~Image() = default;


	private:
		std::size_t m_index = -1;
		Series* m_parent = {};
		std::string m_path = {};
		std::string m_sopInstanceUid = {};
		std::string m_classUid = {};
		std::string m_frameOfReferenceId = {};
		std::string m_modality = {};
		int m_instanceNumber = {};
		int m_windowsCenter = {};
		int m_windowWidth = {};
		int m_rows = {};
		int m_columns = {};
		int m_numberOfFrames = {};
		double m_sliceLocation = {};
		double m_pixelSpacingX = -1;
		double m_pixelSpacingY = -1;
		int m_acquisitionNumber = {};
		bool m_isMultiframe = false;
		vtkWeakPointer<vtkDICOMImageReader> m_imageReader = {};

		static bool isLess(Image* t_lhs, Image* t_rhs);

	};
}

