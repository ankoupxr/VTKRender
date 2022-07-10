#pragma once
#include <string>
#include <vector>
#include "Study.h"

namespace VTKRender 
{
	class Patient
	{
	public:
		Patient();//构造
		Patient(Patient* old);//拷贝构造函数
		~Patient();
	public:
		std::string PatientName;
		std::string PatientID;
		std::vector<Study*> StudyList; //这个病人的Study列表
		int indexOfCurrentStudy; //当前正在读取的Study的索引号.从0开始,默认为0
		int indexOfCurrentSeries;//当前正在读取的Series的索引号,从0开始,默认为0
		int indexOfCurrentImage; //当前正在读取的Image的索引号,从0开始,默认为0

		void reset();//复位

		Study* getCurrentDicomStudy();//获取当前Study
		void setCurrentDicomStudyById(std::string& studyid);//通过studyid设置当前的study

		Series* getCurrentDicomSeries();//获取当前Series
		void setCurrentDicomSeriesById(std::string& seriesnum);//通过seriesnum设置当前的Series

		Image* getCurrentDicomImage();//获取当前Image
		Image* getNextDicomImage();//获取下一张Image,并移动指针,越界自动回到第一张
		Image* getDicomImageByRfid(std::string& rfid);//通过RFID在当前病人的信息中检索出一张图片
		Image* getDicomImageByIndex(int index);//取当前study,当前series的第index张图片,如果越界,返回原来索引所指向的那一张图片
	};
}