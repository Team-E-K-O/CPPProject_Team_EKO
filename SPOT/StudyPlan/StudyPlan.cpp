#include "StudyPlan.h"
#include "../GUI/GUI.h"
#include <iostream>   //debug_e


StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	Notes.push_back("Click here to add a note.");
	for (int i = 0; i < 5; i++) {
		plan.push_back(new AcademicYear);
		graphicsInfo gfx;
		gfx.x = i;
		gfx.y = 1;
		plan[i]->setGfxInfo(gfx);
		plan[i]->SetYearNumber(i+1) ;
	}
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	//std::cout << year<<endl;    //debug_e
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


void StudyPlan::DetYearSemSave(int& year, SEMESTER& Sem)
{
	for (int i = 0; i < plan.size(); i++)
	{
		year = i + 1;
		Sem = FALL;
		Sem = SPRING;
		Sem = SUMMER;
	}
}


void StudyPlan::DrawMe(GUI* pGUI)
{
	pGUI->DrawNotes(Notes);
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DrawMe(pGUI);	
	}
}
void StudyPlan::AddPlanNote(string s)
{
	Notes[0] = "Notes :";
	Notes.push_back(s);
}

void StudyPlan::DeleteStudyPlan(graphicsInfo g,int year, SEMESTER sem)
{
	plan[year - 1]->DeleteCourse(g, sem);
}

void StudyPlan::DeleteALL()
{
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DeleteAll();
	}
}

Course* StudyPlan::ReturnCoursePointer(graphicsInfo g, int year, SEMESTER sem)
{
	return plan[year - 1]->ReturnCoursePointer(g, sem);
}

StudyPlan::~StudyPlan()
{
}

vector<vector<vector<Course>>> StudyPlan::ReturnALlCrs() const
{
	vector<vector<vector<Course>>> all;
	for (auto it : plan)
	{
		
	    vector<vector<Course>> x =(it)->ReturnAllCrs();
		all.push_back(x);
	}
	return all;
}
