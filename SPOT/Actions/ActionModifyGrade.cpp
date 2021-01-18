#include "ActionModifyGrade.h"
#include "..\Registrar.h"



ActionModifyGrade::ActionModifyGrade(Registrar* p) :Action(p)
{
}


bool ActionModifyGrade::Execute()
{
	GUI* pGUI = pReg->getGUI();

	ActionData actData = pGUI->GetUserAction("Click on the course you want modify its grade ...");

	int x, y;

	if (actData.actType == DRAW_AREA)
	{

		x = actData.x;
		y = actData.y;
		graphicsInfo gInfo{ x, y };
		StudyPlan* pp = pReg->getStudyPlan();
		Course* pc = pp->ReturnCoursePointer(gInfo);
		if (pc == nullptr)                              
			return false;
		else
		{
			pc->setSelected(true);
			pc->DrawMe(pGUI);
			bool noError = true;
			pGUI->PrintMsg("Enter the grade of the course (A,A-,-B.......");
			pc->setSelected(false);
			string grade = pGUI->GetSrting();
			if (grade == "A")
				pc->setGrade(A);
			else if (grade == "B+")
				pc->setGrade(BP);
			else if (grade == "B")
				pc->setGrade(B);
			else if (grade == "B-")
				pc->setGrade(BM);
			else if (grade == "C+")
				pc->setGrade(CP);
			else if (grade == "C")
				pc->setGrade(C);
			else if (grade == "C-")
				pc->setGrade(CM);
			else if (grade == "F")
				pc->setGrade(F);
			else
				noError = false;

				ActionData actData = pGUI->GetUserAction(noError ? "Grade modified Successfully ! click anywhere to continue":"Input error ! click anywhere to continue");
		
				return noError;



		}
	}
	return true;

}
ActionModifyGrade :: ~ActionModifyGrade()
{
}