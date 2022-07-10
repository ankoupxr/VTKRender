#pragma once
#ifndef VTKwidgetDICOM_h
#define VTKwidgetDICOM_h

#include "DICOMAppHelper.h"
#include "DICOMParser.h"
#include <vtkIOImageModule.h> 
#include <vtkImageReader2.h>

class vtkDICOMImageReaderVector;
class DICOMParser;
class DICOMAppHelper;

namespace VTKRender 
{

	class VTKwidgetDICOM :public vtkImageReader2
	{
		static VTKwidgetDICOM* New();
		vtkTypeMacro(VTKwidgetDICOM, vtkImageReader2);
		unsigned long getImageDateLength();//获取DICOM图片数据长度
		void PrintSelf(ostream& os,vtkIndent indent) VTK_OVERRIDE;
		void SetDirectoryName(const char* dn);
		void SetFileNames(vtkStringArray*)override;
		vtkGetStringMacro(DirectoryName);
		double* GetPixelSpacing();
		int GetWidth();
		int GetHeight();
		float* GetImagePositionPatient();
		float* GetImageOrientationPatient();
		int GetBitsAllocated();
		int GetPixelRepresentation();
		int GetNumberOfComponents();
		const char* GetTransferSyntaxUID();
		float GetRescaleSlope();
		float GetRescaleOffset();
		const char* GetPatientName();
		const char* GetStudyUID();
		const char* GetStudyID();
		float GetGantryAngle();
		int CanReadFile(const char* fname) VTK_OVERRIDE;
		const char* GetFileExtensions() VTK_OVERRIDE
		{
			return ".dcm";
		}
		const char* GetDescriptiveName() VTK_OVERRIDE
		{
			return "DICOM";
		}
	
	protected:
		void SetupOutputInformation(int num_slices);
		void ExecuteInformation() VTK_OVERRIDE;
		void ExecuteDataWithInformation(vtkDataObject* out, vtkInformation* outInfo) VTK_OVERRIDE;
		VTKwidgetDICOM();
		~VTKwidgetDICOM() VTK_OVERRIDE;

		DICOMParser* Parser;
		DICOMAppHelper* AppHelper;
		vtkDICOMImageReaderVector* DICOMFileNames;
		char* DirectoryName;

		char* PatientName;
		char* StudyUID;
		char* StudyID;
		char* TransferSyntaxUID;

		int GetNumberOfDICOMFileNames();
		const char* GetDICOMFileName(int index);

	private:
		VTKwidgetDICOM(const VTKwidgetDICOM&) VTK_DELETE_FUNCTION;
		void operator=(const VTKwidgetDICOM&) VTK_DELETE_FUNCTION;
	};
}
#endif