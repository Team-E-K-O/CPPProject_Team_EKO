#include "ActionMove.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <iostream>  //debug_e


ActionMove::ActionMove(Registrar* p) :Action(p)
{
}

bool ActionMove::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click on what you want to move ...");
	int x, y,x2,y2;
	if (actData.actType == DRAW_AREA)
	{
		x = actData.x;
		y = actData.y;

		cout << "tst tst" << endl;

		graphicsInfo gInfo{ x, y };

		int year,year2;
		SEMESTER sem,sem2;

		StudyPlan* pp = pReg->getStudyPlay();
		pp->DetYearSem(gInfo, year, sem);
		Course* pc = pp->ReturnCoursePointer(gInfo, year, sem);
		pc->DrawMe(pGUI);
		ActionData actData2 = pGUI->GetUserAction("Choose where you want to move it ...");
		x2 = actData2.x;
		y2 = actData2.y;
		graphicsInfo gInfo2{ x2, y2 };
		pp->DetYearSem(gInfo2, year2, sem2);
		pc->setSelected(false);
		pp->AddCourse(pc, year2, sem2);

		pp->DeleteStudyPlan(gInfo, year, sem);

		

		return true;
	}

}


ActionMove::~ActionMove()
{
}