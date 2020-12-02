#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionAddNote.h"
#include "Actions/ActionDeleteCourse.h"
#include "Actions/ActionMove.h"
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

		break;

	case LOAD:

		break;

	case UNDO:

		break;

	case REDO:

		break;
	case NOTES_AREA :
		//std::cout << "Notes area" << endl;   //debug_e
		RequiredAction = new ActionAddNote(this);
		break;
	case MOVE :
		RequiredAction = new ActionMove(this);
		break;

	//TODO: Add case for each action
	case EXIT:
		running = false;
		break;
	case DEL_CRS:    //delete course action
		RequiredAction = new ActionDeleteCourse(this);

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
	running = true;
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
