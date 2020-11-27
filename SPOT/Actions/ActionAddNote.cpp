#include "ActionAddNote.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

#include <iostream>
ActionAddNote::ActionAddNote(Registrar* p) :Action(p)
{
}

bool ActionAddNote::Execute()
{
	//GUI* pGUI = pReg->getGUI();

	//pGUI->PrintMsg("Add Note:");
	//Course_Code code = pGUI->GetSrting();

	//TODO: add input validation


	int x, y;
	if (actData.actType == NOTES_AREA)	//user clicked inside notes area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;

		GUI* pGUI = pReg->getGUI();

		pGUI->PrintNote("Add Note:");
		Course_Code code = pGUI->GetSrting();

		graphicsInfo gInfo{ x, y };

		//TODO: given course code, get course title, crd hours from registrar
		//For now, we will add any dummy values
		string Title = "Test101";
		pC->setGfxInfo(gInfo);

		//TODO: Ask registrar to add course to the year selected by the user
		//TODO: add the course to the correct year obtained from registrar

		//For the seke of demo, we will add the course to the 1st year, 1st semester
		StudyPlan* pS = pReg->getStudyPlay();
		pS->AddCourse(pC, 1, FALL);
	}


	//TODO:


	return true;
}


ActionAddNote::~ActionAddNote()
{
}