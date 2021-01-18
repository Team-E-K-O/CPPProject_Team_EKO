#include "ActionAddNote.h"
#include "..\Registrar.h"


ActionAddNote::ActionAddNote(Registrar* p) :Action(p)
{
}

bool ActionAddNote::Execute()
{
	bool state = false;
	pReg->getGUI()->PrintMsg("View or add new notes, To exit notes view press Esc Key");
	while (true)
	{
		string newNote = pReg->getGUI()->StartNotesView(pReg->getStudyPlan()->ReturnNotes());
		if (newNote == "")
			break;
		else
		{
			pReg->getStudyPlan()->AddPlanNote(newNote);
			state = true;
		}
	}
	return state;

}


ActionAddNote::~ActionAddNote()
{
}