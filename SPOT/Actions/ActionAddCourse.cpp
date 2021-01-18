#include "ActionAddCourse.h"
#include "..\Registrar.h"


ActionAddCourse::ActionAddCourse(Registrar* p):Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();	
	Rules rls = pReg->ReturnRules();
	
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE 202):");
	Course_Code code = pGUI->GetSrting();
	if (code=="")
	{
		return false;
	}

	//TODO: add input validation
	Course* pC = pReg->CreateCourseP(code);
	
	if (pC)            // Pointer is null in case of un existing code
	{
		ActionData actData = pGUI->GetUserAction("Select a and semister year to add course to:");
		int x, y;
		if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
		{
			//get coord where user clicked
			x = actData.x;
			y = actData.y;



			graphicsInfo gInfo{ x, y };

			//TODO: given course code, get course title, crd hours from registrar
		
			

			//TODO: Ask registrar to add course to the year selected by the user
			//TODO: add the course to the correct year obtained from registrar
			int year;
			SEMESTER Sem;
			StudyPlan* pS = pReg->getStudyPlan();
			pS->DetYearSem(gInfo, year, Sem);
			pS->AddCourse(pC, year, Sem);
		}
	}
	else
		ActionData actData = pGUI->GetUserAction("Error ! Code not found press anywhere to continue");
	
	//TODO:
	

	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}
