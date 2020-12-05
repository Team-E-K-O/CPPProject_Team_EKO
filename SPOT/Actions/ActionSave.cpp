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

	int year;
	SEMESTER sem;

	StudyPlan* pp = pReg->getStudyPlay();
	//pp->SaveStudyPlan(year, sem);

	ofstream myfile;
	myfile.open(filename + ".txt");

	myfile <<
		"Year1:\n"
		"\tFall: \n"
		"\tSpring: \n"
		"\tSummer: \n"
		"Year2:\n"
		"\tFall: \n"
		"\tSpring: \n"
		"\tSummer: \n"
		"Year3:\n"
		"\tFall: \n"
		"\tSpring: \n"
		"\tSummer: \n"
		"Year4:\n"
		"\tFall: \n"
		"\tSpring: \n"
		"\tSummer: \n"
		"Year5:\n"
		"\tFall: \n"
		"\tSpring: \n"
		"\tSummer: \n";

	myfile.close();
	return true;
}


ActionSave::~ActionSave()
{
}