#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "ActionDeleteCourse.h"
#include <iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) :Action(p)
{
}

bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click on the course you want to delete ...");

	int x, y;
	if (actData.actType == DRAW_AREA)
	{

		x = actData.x;
		y = actData.y;
		graphicsInfo gInfo{ x, y };
		StudyPlan* pp = pReg->getStudyPlan();
		pp->DeleteCrs(gInfo);
		delete pp->ReturnCoursePointer(gInfo);
		return true;
	}

}


ActionDeleteCourse::~ActionDeleteCourse()
{
}