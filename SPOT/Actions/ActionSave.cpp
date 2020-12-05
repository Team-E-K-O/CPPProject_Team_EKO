#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "ActionSave.h"
#include <string>
#include <iostream>
#include <fstream>

ActionSave::ActionSave(Registrar* p) :Action(p)
{
}

bool ActionSave::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Write the name of the .txt file: ");

	string filename = pGUI->GetSrting();

	StudyPlan* pp = pReg->getStudyPlay();

	ofstream myfile;
	myfile.open(filename + ".txt");

	int year;
	SEMESTER sem; 
	
	pp->DetYearSemSave(year, sem);
	cout << year << endl << sem << endl;
	myfile <<
		"Year1:\n"
		"\tFall: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSpring: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSummer: " << pp->SaveStudyPlan(year, sem) << endl <<
		"Year2:\n"
		"\tFall: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSpring: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSummer: " << pp->SaveStudyPlan(year, sem) << endl <<
		"Year3:\n"
		"\tFall: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSpring: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSummer: " << pp->SaveStudyPlan(year, sem) << endl <<
		"Year4:\n"
		"\tFall: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSpring: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSummer: " << pp->SaveStudyPlan(year, sem) << endl <<
		"Year5:\n"
		"\tFall: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSpring: " << pp->SaveStudyPlan(year, sem) << endl <<
		"\tSummer: " << pp->SaveStudyPlan(year, sem) << endl;

	myfile.close();
	return true;
}


ActionSave::~ActionSave()
{
}