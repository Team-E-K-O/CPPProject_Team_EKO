#include "ActionDeleteCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "Drawable.h"
#include <iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) :Action(p)
{
}

bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click On What You Wish To Delete....");

	int x, y;
	if (actData.actType == DRAW_AREA)
	{
		x = actData.x;
		y = actData.y;

		graphicsInfo gInfo{ x, y };

		Registrar p;
		p.Run();
		pGUI->ClearDrawingArea();
	}
	return true;
}


ActionDeleteCourse::~ActionDeleteCourse()
{
}