#include "ActionCoursetype.h"
#include "..\Registrar.h"
#include "UnivCourse.h"



ActionCoursetype::ActionCoursetype(Registrar* p):Action(p)
{
}


bool ActionCoursetype::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click on the course you want change its State ...");

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


		if (pc == nullptr)
			return false;
		else
		{
			pc->setSelected(true);
			pc->DrawMe(pGUI);

			pGUI->PrintMsg("Write the type of the course : (done , pending , in progress)");
			pc->setSelected(false);
			string type = pGUI->GetSrting();
			if (type == "")
				return false;


			if (type == "done" || type == "DONE" || type == "Done")
			{
				pc->settype("done");
				ActionData actData = pGUI->GetUserAction("Type Edited Successfully ! press anywhere to continue");
			}
			else if (type == "in progress" || type == "IN PROGRESS" || type == "In Progress")
			{
				pc->settype("in progress");
				ActionData actData = pGUI->GetUserAction("Type Edited Successfully ! press anywhere to continue");
			}
			else if (type == "pending" || type == "PENDING" || type == "Pending")
			{
				pc->settype("pending");
				ActionData actData = pGUI->GetUserAction("Type Edited Successfully ! press anywhere to continue");
			}
			else
				return false;



		}
	}
	return true;
}

ActionCoursetype :: ~ActionCoursetype()
{
}