#include "..\Registrar.h"

#include "ActionDeleteCourse.h"

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
		if (!pp->ReturnCoursePointer(gInfo))
			return false;
		pp->DeleteCourse(gInfo);
		delete pp->ReturnCoursePointer(gInfo);
		return true;
	}

}


ActionDeleteCourse::~ActionDeleteCourse()
{
}