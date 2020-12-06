#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

ActionAddCourse::ActionAddCourse(Registrar* p):Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();	
	
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE 202):");
	Course_Code code = pGUI->GetSrting();

	//TODO: add input validation


	ActionData actData = pGUI->GetUserAction("Select a and semister year to add course to:");
	//TODO: add input validation

	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		
		
		
		graphicsInfo gInfo{ x, y };

		//TODO: given course code, get course title, crd hours from registrar
		//For now, we will add any dummy values
		string Title = "Test101";
		int crd = 0;
		Course* pC = new Course(code, Title, crd);
		//TODO: Ask registrar to add course to the year selected by the user
		//TODO: add the course to the correct year obtained from registrar

		//For the seke of demo, we will add the course to the 1st year, 1st semester
		int year;
		SEMESTER Sem;
		StudyPlan* pS = pReg->getStudyPlay();
		pS->DetYearSem(gInfo, year, Sem);
		pS->AddCourse(pC, year, Sem);
	}

	
	//TODO:
	

	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}
