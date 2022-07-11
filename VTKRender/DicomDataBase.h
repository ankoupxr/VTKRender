#pragma once
#include <string>
#include <vector>
#include "Patient.h"


namespace VTKRender {

	class DicomDataBase
	{
	public:
		static DicomDataBase* getInstance();
		void Init(std::string dir);//��DICOMDIR�ļ���ʼ��
		void InitFromSingleImage(std::string ImageFileName);//�ӵ���ͼƬ��ʼ��
		void InitFromSeriesFolder(std::string SeriesFolder);//��seriesfolder��ʼ��
	private:
		//static DicomDataBase* m_pSingleton;
		DicomDataBase();
		~DicomDataBase();
	public:
		std::vector<Patient*> PatientList;//���ݿ��б�������еĲ���
		std::string DicomDirFilePath;//DicomDir�ļ��ľ���·��
		std::string DicomForderPath;//DicomDIR�ļ����ڵ��ļ���,�ں������RefFileID�͵õ�ͼƬ�ľ���·��
		Patient* getPatientById(std::string& patientid);//ʹ��patient id��ѯһ��patient����
		Patient* get_previous_patient(Patient* current_patient); //��ȡǰһ������
		Patient* get_latter_patient(Patient* current_patient);//��ȡ��һ������
	};
}
