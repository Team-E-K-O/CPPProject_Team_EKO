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

	pGUI->PrintMsg("Add Note:");
	string note = pGUI->GetSrting();

	ActionData actData = pGUI->GetUserAction();


	int x, y;
	if (actData.actType == NOTES_AREA)	//user clicked inside notes area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;

		GUI* pGUI = pReg->getGUI();

		pGUI->PrintNote(note,x,y);
		

		
	}





	return true;
}


ActionAddNote::~ActionAddNote()
{
}