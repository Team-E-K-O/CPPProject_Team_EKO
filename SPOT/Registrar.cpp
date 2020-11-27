#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include <iostream>   //debug_e

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick an action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		
		break;
	case SAVE:
		//std::cout << "save" << endl;   //debug_e
		break;
	case LOAD:
		//std::cout << "load" << endl;    //debug_e
		break;
	case UNDO:
		//std::cout << "undo" << endl;     //debug_e
		break;
    case DEL_CRS:
		//std::cout << "lol"; //debug_e       //debug_e
		break;
	case REDO:
		//std::cout << "redo" << endl;       //debug_e
		break;
	case NOTES_AREA:
		std::cout << "Notes area" << endl;   //debug_e
		break;

	//TODO: Add case for each action
	case EXIT:
		running = false;
		//std::cout << "fck u";   //debug_e
		break;
		
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (running)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

Registrar::~Registrar()
{
	delete pGUI;
}
