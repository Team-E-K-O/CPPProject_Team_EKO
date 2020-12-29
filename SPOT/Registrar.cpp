#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "Actions/ActionAddNote.h"
#include "Actions/ActionDeleteCourse.h"
#include "Actions/ActionMove.h"
#include "Actions/ActionMove.h"
#include "Actions/ActionEditCourseCode.h"
#include"Actions/ActionSave.h"
#include"Actions/ActionSave.h"
#include "Actions/ActionImportSplan.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

Registrar::Registrar()
{ 
	ImportRules();
	GetCourseCatalog();                      //Disabled untill a catalog file is uploaded cuz it wil cause the program to crash
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	Push2Stack();

}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlan() const
{
	return pSPlan;
}

Rules Registrar::ReturnRules() const
{
	return RegRules;
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
	case DRAW_AREA :
	{
		
		{
			pGUI->ClearStatusBar();
			int x, y;
			x = actData.x;
			y = actData.y;
			graphicsInfo gInfo{ x,y };
			int year;
			SEMESTER sem;
			StudyPlan* pp = getStudyPlan();
			pp->DetYearSem(gInfo, year, sem);
			Course* pc = pp->ReturnCoursePointer(gInfo, year, sem);
			if (pc == nullptr)
			{
				break;
			}
			else
			{

				pc->setSelected(true);
				pc->DrawMe(pGUI);
				string pc2 = to_string(pc->getCredits());
				string title = pc->getTitle();
				string code = pc->getCode();
				string courseinfo ="Title: " +  title + ", " + "Code: " + code + ", " + "Credits: " + pc2;
				ActionData actData = pGUI->GetUserAction(courseinfo);
				pc->setSelected(0);
				break;
			}
		}
	}
	case SAVE:
		RequiredAction = new ActionSave(this);
		break;

	case LOAD:
		RequiredAction = new ActionImportSplan(this);
		break;

	case UNDO:
		UndoF();
		break;

	case REDO:
		RedoF();
		break;
	case NOTES_AREA :
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
	case EDIT:  // Edit course in the study plan
		RequiredAction = new ActionEditCourseCode(this);
		
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
			if (ExecuteAction(pAct))   //if action is not cancelled
			{
				Push2Stack();
				//UpdateInterface();   //useless i think !
			}
		}	
	}
}

void Registrar::Push2Stack()
{
	StudyPlan temp;
	temp = *(pSPlan);
	temp.StaticCopyit(pSPlan);
	UndoS.push(temp);
}

void Registrar::UndoF()
{
	if (UndoS.size() >1 )
	{
		RedoS.push(UndoS.top());
		UndoS.pop();
		PlanTemp = UndoS.top();
		pSPlan =& PlanTemp;
	}
}

void Registrar::RedoF()
{
	if (RedoS.size()>0)
	{
		UndoS.push(RedoS.top());
		PlanTemp = UndoS.top();
		pSPlan = &PlanTemp;
		RedoS.pop();
	}
}



void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items      //test
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}
void Registrar::GetCourseCatalog()
{
	string file_name = "CourseCatalog.txt";
	vector<vector<string>> Words;
	string Line;
	ifstream Myfile(file_name);
	if (Myfile.is_open())
	{
		while (getline(Myfile, Line))
		{
			stringstream ssLine(Line);
			string Word;
			vector<string> linewrds;
			while (getline(ssLine, Word, ','))
				linewrds.push_back(Word);
			Words.push_back(linewrds);
		}
		for (auto w :Words )
		{	
		CourseInfo c;
		c.Title = w[1];
		c.Code = w[0];
		/*for (int i = 2; i < 5; i++)    
			c.PreReqList.push_back(w[i]);
		for (int i = 5; i < 8; i++)
			c.CoReqList.push_back(w[i]);*/
		char s = w[2][0];
		c.Credits = s - '0';
		//c.type = w[9];
		RegRules.CourseCatalog.push_back(c);
		}


	}
}

void Registrar::ImportRules()
{
	string file_name = "Rules.txt";
	vector<vector<string>> Words;
	string Line;
	ifstream Myfile(file_name);
	if (Myfile.is_open())
	{
		while (getline(Myfile, Line))
		{
			stringstream ssLine(Line);
			string Word;
			vector<string> linewrds;
			while (getline(ssLine, Word, ','))
				linewrds.push_back(Word);
			Words.push_back(linewrds);
		}

		RegRules.TotalCredit = stoi(Words[0][0]);
		RegRules.ReqUnivCompulsoryCredits = stoi(Words[1][0]);
		RegRules.ReqUnivElectiveCredits = stoi(Words[1][1]);
		RegRules.ReqTrackCredits = stoi(Words[2][0]);
		RegRules.ReqMajorCompulsoryCredits = stoi(Words[3][0]);
		RegRules.ReqMajorElectiveCredits = stoi(Words[3][1]);
		for (auto var : Words[4])
		{
			Course_Code x = var;
			RegRules.UnivCompulsory.push_back(x);
		}
		for (auto var : Words[5])
		{
			Course_Code x = var;
			RegRules.UnivElective.push_back(x);
		}
		for (auto var : Words[6])
		{
			Course_Code x = var;
			RegRules.TrackCompulsory.push_back(x);
		}
		for (auto var : Words[7])
		{
			Course_Code x = var;
			RegRules.MajorCompulsory.push_back(x);
		}
		for (auto var : Words[8])
		{
			Course_Code x = var;
			RegRules.MajorElective.push_back(x);
		}
	}
}


Course * Registrar::CreateCourseP(Course_Code code)
{
	bool state = true;
	for (auto i : RegRules.CourseCatalog)
	{
		if (code == i.Code)
		{
			string title = i.Title;
			int credits = i.Credits;
			Course* pC = new Course(code, title, credits);
			return pC;
			state = false;
			break;
		}
	}
	if(state)
	return nullptr;
}
Registrar::~Registrar()
{
	delete pGUI;
}
