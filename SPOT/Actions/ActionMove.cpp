#include "ActionMove.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"


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

		graphicsInfo gInfo{ x, y };

		int year,year2;
		SEMESTER sem,sem2;

		StudyPlan* pp = pReg->getStudyPlay();
		pp->DetYearSem(gInfo, year, sem);
		Course* pc = pp->ReturnCoursePointer(gInfo, year, sem);
		
		while (true)
		{
			if (pc == nullptr)
			{
				break;
			}
			else
			{
				pc->setSelected(true);
				pc->DrawMe(pGUI);
				ActionData actData2 = pGUI->GetUserAction("Choose where you want to move it ...");
				if (actData2.actType == DRAW_AREA)
				{
					x2 = actData2.x;
					y2 = actData2.y;
					graphicsInfo gInfo2{ x2, y2 };
					pp->DetYearSem(gInfo2, year2, sem2);
					pc->setSelected(false);
					pp->AddCourse(pc, year2, sem2);
					pp->DeleteStudyPlan(gInfo, year, sem);
					break;
				}
			}
			
		}

		return true;
	}

}


ActionMove::~ActionMove()
{
}