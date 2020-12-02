#include "ActionAddNote.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

#include <iostream>
ActionAddNote::ActionAddNote(Registrar* p) :Action(p)
{
}

bool ActionAddNote::Execute()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* Ps = pReg->getStudyPlay();
	pGUI->PrintMsg("Add Note:");
	string note = pGUI->GetSrting();
	Ps->AddPlanNote(note);
	//test test test
	return true;
}


ActionAddNote::~ActionAddNote()
{
}