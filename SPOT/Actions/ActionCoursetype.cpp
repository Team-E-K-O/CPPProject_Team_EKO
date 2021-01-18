#include "ActionCoursetype.h"
#include "..\Registrar.h"
#include "UnivCourse.h"


ActionCoursetype::ActionCoursetype(Registrar* p):Action(p)
{
}


bool ActionCoursetype::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click on the course you want change it's type ...");

	int x, y;

	if (actData.actType == DRAW_AREA)
	{

		x = actData.x;
		y = actData.y;
		graphicsInfo gInfo{ x, y };

		int year;
		SEMESTER sem;

		StudyPlan* pp = pReg->getStudyPlan();
		pp->DetYearSem(gInfo, year, sem);
		Course* pc = pp->ReturnCoursePointer(gInfo);
		
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

				pGUI->PrintMsg("Write the type of the course :");
				pc->setSelected(false);
				string type = pGUI->GetSrting();
				if (type == "")
					return false;


				if (type == "done")
				{
					pc->settype(type);
					ActionData actData = pGUI->GetUserAction("Type Edited Successfully ! press anywhere to continue");
				}
				else if (type == "in progress")
				{
					pc->settype(type);
					ActionData actData = pGUI->GetUserAction("Type Edited Successfully ! press anywhere to continue");
				}
				else if (type == "pending")
				{
					pc->settype(type);
					ActionData actData = pGUI->GetUserAction("Type Edited Successfully ! press anywhere to continue");
				}

				break;
			}
		}

		return true;
	}


	return true;
}

ActionCoursetype :: ~ActionCoursetype()
{
}