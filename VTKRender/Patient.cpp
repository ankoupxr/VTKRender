#include "Patient.h"

#include <string>
#include <vector>
#include "Study.h"


namespace VTKRender
{
	#include "Patient.h"


/*
 * 默认构造函数
 */
	VTKRender::Patient::Patient()
{
	indexOfCurrentStudy = 0; 
	indexOfCurrentSeries = 0;
	indexOfCurrentImage = 0;
}
/*
 * 拷贝构造函数
 * 对于Patient对象进行深拷贝,但是对于Studylist中索引的和间接索引的对象是地址拷贝
 * 也就是浅拷贝,由于数据类这边不需要进行写操纵,所以这是无所谓的,只要读出的值是对的
 * 就可以了
 * 为了防止不必要的麻烦,未来应该进行属性封装阻止一切来自外部的对指针的修改
 */
	VTKRender::Patient::Patient(Patient * old)
{
	this->PatientName = old->PatientName;
	this->PatientID =old->PatientID;
	this->indexOfCurrentStudy = old->indexOfCurrentStudy; 
	this->indexOfCurrentSeries = old->indexOfCurrentSeries;
	this->indexOfCurrentImage = old->indexOfCurrentImage; 

	for(int i=0;i<old->StudyList.size();i++)
	{
		this->StudyList.push_back(old->StudyList[i]);
	}
}
/*
 * 析构
 */
	VTKRender::Patient::~Patient()
{
}
/*
 * 复位,将所有的索引复位
 */
void VTKRender::Patient::reset()
{
	indexOfCurrentStudy = 0;
	indexOfCurrentSeries = 0;
	indexOfCurrentImage = 0;
}
/*
 * 获取当前Study
 */
Study * VTKRender::Patient::getCurrentDicomStudy()
{
	return this->StudyList[indexOfCurrentStudy];
}
/*
 * 通过studyid设置当前的study
 */
void VTKRender::Patient::setCurrentDicomStudyById(std::string &studyid)
{
	int index = 0;
	for(index=0;index<this->StudyList.size(); index++)
	{
		if (StudyList[index]->StudyId == studyid)
		{
			indexOfCurrentStudy = index;
			return;
		}
	}
	indexOfCurrentStudy = 0;
}
/*
 * 获取当前Series
 */
Series * VTKRender::Patient::getCurrentDicomSeries()
{
	return this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries];
}
/*
 * 通过seriesnum设置当前的Series
 */
void VTKRender::Patient::setCurrentDicomSeriesById(std::string & seriesnum)
{
	//检索所有的series,检索到的时候直接把study和series索引全都切换
	for(int i=0;i<this->StudyList.size();i++)
	{
		for(int j=0;j<this->StudyList[i]->SeriesList.size();j++)
		{
			if(this->StudyList[i]->SeriesList[j]->SeriseNumber==seriesnum)
			{
				indexOfCurrentSeries = j;
				indexOfCurrentStudy = i;
				indexOfCurrentImage = 0;
				return;
			}
		}
	}
}
/*
 * 获取当前Image
 */
Image * VTKRender::Patient::getCurrentDicomImage()
{
	return this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries]->ImageList[indexOfCurrentImage];
}
/*
 * 获取下一张Image,并移动指针,越界自动回到第一张
 */
Image * VTKRender::Patient::getNextDicomImage()
{
	indexOfCurrentImage = 
		(indexOfCurrentImage == StudyList[indexOfCurrentStudy]->
								SeriesList[indexOfCurrentSeries]->
								ImageList.size() - 1 ?
								0 : indexOfCurrentImage + 1);
	return getCurrentDicomImage();
}
	/*
	 * 通过RFID在当前病人的信息中检索出一张图片
	 */
	Image * VTKRender::Patient::getDicomImageByRfid(std::string & rfid)
	{
		//检索这个病人的全部Image
		//一旦检索成功,立即切换Study,Series,Image的Current索引,并返回当前图片
		for(int i=0;i<this->StudyList.size();i++)
		{
			for(int j=0;j<this->StudyList[i]->SeriesList.size();j++)
			{
				for(int k=0;k<this->StudyList[i]->SeriesList[j]->ImageList.size();k++)
				{
					if(this->StudyList[i]->SeriesList[j]->ImageList[k]->ReferencedFileID== rfid)
					{
						indexOfCurrentStudy = i;
						indexOfCurrentSeries = j;
						indexOfCurrentImage = k;
						return  getCurrentDicomImage();
					}
				}
			}
		}
	}
	/*
	 * 取当前study,当前series的第index张图片,如果越界,返回原来索引所指向的那一张图片
	 * index从0开始
	 */
	Image * VTKRender::Patient::getDicomImageByIndex(int index)
	 {
		 if (index>this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries]->ImageList.size())
		 {
			 //越界,返回当前图片
			 return getCurrentDicomImage();
		 }else
		 {
			 indexOfCurrentImage = index;
			 return this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries]->ImageList[indexOfCurrentImage];
		 }
	 }

}