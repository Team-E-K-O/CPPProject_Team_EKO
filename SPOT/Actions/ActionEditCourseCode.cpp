#include "ActionEditCourseCode.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <iostream>  //debug_e


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

		StudyPlan* pp = pReg->getStudyPlay();
		pp->DetYearSem(gInfo, year, sem);
		Course* pc = pp->ReturnCoursePointer(gInfo, year, sem);
		pc->setSelected(true);
		pc->DrawMe(pGUI);

		while (true)
		{
			pGUI->PrintMsg("Enter The New Course Code: Enter course Code(e.g. CIE202):");

			Course_Code code = pGUI->GetSrting();
			
			pc->setSelected(false);

			string Title = "Test101";

			int crd = 0;

			Course* pC = new Course(code, Title, crd);

			pC->setGfxInfo(gInfo);

			pp->DetYearSem(gInfo, year, sem);

			pp->AddCourse(pc, year, sem);

			pp->DeleteStudyPlan(gInfo, year, sem);

			break;
		}


		return true;
	}

}


ActionEditCourseCode::~ActionEditCourseCode()
{
}