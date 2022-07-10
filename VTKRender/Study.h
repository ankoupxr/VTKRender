#pragma once

#include <string>
#include <vector>
#include "Series.h"


namespace VTKRender
{
	class  Study
	{
	public:
		Study();
		~Study();

	public:
		std::string ModulationType;
		std::string InstitutionName;
		std::string PatientBirthDate;
		std::string PatientSex;
		std::string PatientAge;
		std::string StudyId;
		std::vector<Series*> SeriesList;
	};
}
