#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include <vector>
#include <iostream>    //debug
using namespace std;

AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
	for (int sem = FALL; sem < SEM_CNT; sem++)
		NumberOfCourses[sem] = 0;
}



AcademicYear::~AcademicYear()
{
	/*for (int sem = 0; sem < 3; sem++)
	{
		for (Course* crs : YearCourses[sem])
			delete crs;
	}*/
}
int AcademicYear::GetYearNumber() const
{
	return YearNumber;
}
void AcademicYear::SetYearNumber(int x)
{
	YearNumber = x;
}
//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	
	if (pC)
	{
		YearCourses[sem].push_back(pC);
		TotalCredits += pC->getCredits();
		NumberOfCourses[sem]++;
		//TODO: acording to course type incremenet corrsponding toatl hours for that year
		if (pC->getCourseType() == univ)
			TotalUnivCredits+=pC->getCredits();
		else if(pC->getCourseType() == major)
			TotalMajorCredits += pC->getCredits();
		else if (pC->getCourseType() == track)
			TotalTrackCredits += pC->getCredits();

		
		return true;
	}
	else
		return false;
}


void AcademicYear::DrawMe(GUI* pGUI) 
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		int n = 0;
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			
			pGUI->SetCourseLocation(this,* it, sem, n);
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
			n++;
		}
	}
}
int AcademicYear::GetNumCourses(int sem) const
{
	return NumberOfCourses[sem];
}


void AcademicYear::DeleteCourse(graphicsInfo g,SEMESTER sem)
{
	for (Course *  crs :YearCourses[sem])
	{
		if (crs->isClicked(g))
		{
			YearCourses[sem].remove(crs);
			NumberOfCourses[sem]--;
			TotalCredits -= crs->getCredits();
			break;
		}
	}
}

void AcademicYear::DeleteAll()
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto x : YearCourses[sem])
			delete x;
		YearCourses[sem].clear();
		NumberOfCourses[sem]=0;
	}
	TotalCredits = 0;
}

Course* AcademicYear::ReturnCoursePointer(graphicsInfo g, SEMESTER sem)
{
		bool t = false;

	for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
	{
		if ((*it)->isClicked(g))
		{
			t = true;
			return *it;
			
			break;
		}
	}
	if (!t)
		return nullptr;
}

Course* AcademicYear::ReturnCoursePointer(Course_Code code)
{
	bool t = false;
	for (int sem = 0; sem < 3; sem++)
	{
		for (Course* crs :YearCourses[sem])
		{
			if (crs->getCode()==code)
			{
				t = true;
				return crs;
				break;
			}	
		}
		if (t)
			break;
		}
	if (!t)
		return nullptr;
}

vector<vector<Course>> AcademicYear::ReturnAllCrs() const
{
	vector<vector<Course>> yr;

	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		auto term = YearCourses[sem];
		vector<Course> termcrs;
		for (auto it : term)
		{
			termcrs.push_back(*it);
		}
		yr.push_back(termcrs);
		
	}
	return yr;
}


