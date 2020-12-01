#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include <iostream>  //debug_e
AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	pC->setDim(CRS_WIDTH, CRS_HEIGHT);

	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits(); 
	graphicsInfo g= getGfxInfo();
	g.y = g.y + 18 + YearCourses[sem].size() * (pC->getDimh()+10);
	g.x  = g.x + sem * getDimw() / 3;
	std::cout << YearCourses[sem].size() << endl;   //debug_e
	std::cout << g.x << "   " << g.y << endl;        //debug_e
	pC->setGfxInfo(g);



	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}


void AcademicYear::DrawMe(GUI* pGUI) 
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}