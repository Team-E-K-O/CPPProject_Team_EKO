#include"ActionDeleteCourse.h"
#include"..\Registrar.h"
#include"Courses/UnivCourse.h"
#include<iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) :Action(p)
{
}

bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Click On The Course You Wish To Delete....");


	ActionData actData = pGUI->GetUserAction("Coming SOON ♥");

	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing
	{
		x = actData.x;
		y = actData.y;


		graphicsInfo gInfo{ x, y };

		//TODO: given course code, get course title, crd hours from registrar
		//For now, we will add any dummy values
		string Title = "";
		int crd = 0;
	}


	return true;
}