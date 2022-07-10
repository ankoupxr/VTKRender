#pragma once
#include <string>
#include <vector>
#include "Study.h"

namespace VTKRender 
{
	class Patient
	{
	public:
		Patient();//����
		Patient(Patient* old);//�������캯��
		~Patient();
	public:
		std::string PatientName;
		std::string PatientID;
		std::vector<Study*> StudyList; //������˵�Study�б�
		int indexOfCurrentStudy; //��ǰ���ڶ�ȡ��Study��������.��0��ʼ,Ĭ��Ϊ0
		int indexOfCurrentSeries;//��ǰ���ڶ�ȡ��Series��������,��0��ʼ,Ĭ��Ϊ0
		int indexOfCurrentImage; //��ǰ���ڶ�ȡ��Image��������,��0��ʼ,Ĭ��Ϊ0

		void reset();//��λ

		Study* getCurrentDicomStudy();//��ȡ��ǰStudy
		void setCurrentDicomStudyById(std::string& studyid);//ͨ��studyid���õ�ǰ��study

		Series* getCurrentDicomSeries();//��ȡ��ǰSeries
		void setCurrentDicomSeriesById(std::string& seriesnum);//ͨ��seriesnum���õ�ǰ��Series

		Image* getCurrentDicomImage();//��ȡ��ǰImage
		Image* getNextDicomImage();//��ȡ��һ��Image,���ƶ�ָ��,Խ���Զ��ص���һ��
		Image* getDicomImageByRfid(std::string& rfid);//ͨ��RFID�ڵ�ǰ���˵���Ϣ�м�����һ��ͼƬ
		Image* getDicomImageByIndex(int index);//ȡ��ǰstudy,��ǰseries�ĵ�index��ͼƬ,���Խ��,����ԭ��������ָ�����һ��ͼƬ
	};
}