#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include <vector>
using namespace std;
AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
	for (int sem = FALL; sem < SEM_CNT; sem++)
		NumberOfCourses[sem] = 0;
}


AcademicYear::~AcademicYear()
{
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
	

	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits(); 
	NumberOfCourses[sem]++;
	//graphicsInfo g= getGfxInfo();
	//g.y = g.y + 18 + YearCourses[sem].size() * (pC->getDimh()+10);
	//g.x  = g.x + sem * getDimw() / 3;
	//std::cout << YearCourses[sem].size() << endl;   //debug_e
	//std::cout << g.x << "   " << g.y << endl;        //debug_e
	//pC->setGfxInfo(g);



	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
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
			
			pGUI->RedrawCourse(this,* it, sem, n);
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
	auto  sem_ = YearCourses[sem];   /////
	for (auto  crs = sem_.begin(); crs != sem_.end() ; ++crs)
	{
		if ((*crs)->isClicked(g))
		{
			sem_.erase(crs);
			YearCourses[sem] = sem_;
			NumberOfCourses[sem]--;
			break;
		}
	}
}

void AcademicYear::DeleteAll()
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		YearCourses[sem].clear();
		NumberOfCourses[sem]=0;
	}
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


