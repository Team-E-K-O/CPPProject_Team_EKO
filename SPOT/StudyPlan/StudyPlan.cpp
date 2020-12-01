#include "StudyPlan.h"
#include <iostream>   //debug_e


StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++) {
		plan.push_back(new AcademicYear);
		graphicsInfo gfx;
		gfx.x = i;
		gfx.y = 1;
		plan[i]->setGfxInfo(gfx);
		plan[i]->YearNumber = i + 1;
	}
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	std::cout << year<<endl;    //debug_e
	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}
void StudyPlan::DetYearSem(graphicsInfo g, int& year, SEMESTER& Sem) 
{
	for (int i = 0; i < plan.size(); i++)
		if (plan[i]->isClicked(g))
		{
			year = i + 1;
			graphicsInfo  g1 = plan[i]->getGfxInfo();
			if (g.x < g1.x + plan[i]->getDimw() / 3)
				Sem = FALL;
			else if (g.x >= g1.x + plan[i]->getDimw() / 3 && g.x < g1.x + 2 * plan[i]->getDimw() / 3)
				Sem = SPRING;
			else
				Sem = SUMMER;
			break;
		}

}
void StudyPlan::DrawMe(GUI* pGUI)
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DrawMe(pGUI);
		
	}
		
	
}

void StudyPlan::DeleteStudyPlan(graphicsInfo g,int year, SEMESTER sem)
{
	plan[year - 1]->DeleteCourse(g, sem);
}

StudyPlan::~StudyPlan()
{
}
