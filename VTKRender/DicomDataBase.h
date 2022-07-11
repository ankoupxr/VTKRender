#pragma once
#include <string>
#include <vector>
#include "Patient.h"


namespace VTKRender {

	class DicomDataBase
	{
	public:
		static DicomDataBase* getInstance();
		void Init(std::string dir);//从DICOMDIR文件初始化
		void InitFromSingleImage(std::string ImageFileName);//从单张图片初始化
		void InitFromSeriesFolder(std::string SeriesFolder);//从seriesfolder初始化
	private:
		//static DicomDataBase* m_pSingleton;
		DicomDataBase();
		~DicomDataBase();
	public:
		std::vector<Patient*> PatientList;//数据库中保存的所有的病人
		std::string DicomDirFilePath;//DicomDir文件的绝对路径
		std::string DicomForderPath;//DicomDIR文件所在的文件夹,在后面接上RefFileID就得到图片的绝对路径
		Patient* getPatientById(std::string& patientid);//使用patient id查询一个patient对象
		Patient* get_previous_patient(Patient* current_patient); //获取前一个病人
		Patient* get_latter_patient(Patient* current_patient);//获取后一个病人
	};
}
