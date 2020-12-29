#include "ActionEditCourseCode.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"


ActionEditCourseCode::ActionEditCourseCode(Registrar* p) :Action(p)
{
}

bool ActionEditCourseCode::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click on what you want to edit ...");
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

				pGUI->PrintMsg("Enter The New Course Code: Enter course Code(e.g. CIE202):");
				pc->setSelected(false);
				Course_Code code = pGUI->GetSrting();

				

				Course* pC2 = pReg->CreateCourseP(code);
				if (pC2) {


					pC2->setGfxInfo(gInfo);
					pp->DeleteStudyPlan(gInfo);

					pp->DetYearSem(gInfo, year, sem);

					pp->AddCourse(pC2, year, sem);
				}
				else
					ActionData actData = pGUI->GetUserAction("Error ! Code not found press anywhere to continue");

				break;
			}
			
		}
			
		return true;
	}

}


ActionEditCourseCode::~ActionEditCourseCode()
{
}