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
#include "ActionCoursetype.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream> //debug
using namespace std;

void Registrar::CheckRules()
{
	CurrentReqs.TotalCredsAchieved = (pSPlan->GetTotalcrds() >= RegRules.TotalCredit);
	CurrentReqs.MajorCredsAchieved = (pSPlan->GetMajorcrds() >= RegRules.ReqMajorCompulsoryCredits);
	CurrentReqs.UniversityCredsAchieved = (pSPlan->GetUnivcrds() >= RegRules.ReqUnivCompulsoryCredits);
	
	CurrentReqs.TrackCredsAchieved = (pSPlan->GetTrackcrds() >= RegRules.ReqTrackCredits);
	CurrentReqs.MajorCoursesAchieved = true, CurrentReqs.UniversityCoursesAchieved = true, CurrentReqs.TrackCoursesAchieved = true;
	/// Check if one of the university courses is missing
	for (auto crs : RegRules.UnivCompulsory)
	{
		if (pSPlan->ReturnCoursePointer(crs) == nullptr)
		{
			CurrentReqs.UniversityCoursesAchieved = false;
			break;
		}
	}
	/// Check if one of the Track courses is missing
	for (auto crs : RegRules.TrackCompulsory)
	{
		if (pSPlan->ReturnCoursePointer(crs) == nullptr)
		{
			CurrentReqs.TrackCoursesAchieved = false;
			break;
		}
	}
	/// Check if one of the Major courses is missing
	for (auto crs : RegRules.MajorCompulsory)
	{
		if (pSPlan->ReturnCoursePointer(crs) == nullptr)
		{
			CurrentReqs.MajorCoursesAchieved = false;
			break;
		}
	}
}

void Registrar::Checkcrdts()
{
	vector<vector<vector<Course>>> allcrs = pSPlan->ReturnALlCrs();
	bool flag = false;
	for (int y = 0; y < 5; y++)
	{
		if (flag)
		{
			break;
		}
		for (int s = 0; s < 3; s++)
		{
			int crdts = pSPlan->CheckMinMaxCr(y, s);
			if (s == 2)
			{
				if (crdts > 6)
				{
					CurrentReqs.semcrdtError = true;
				}
				else
				{
					CurrentReqs.semcrdtError = false;
					flag = true;
					break;
				}
			}
			else
			{
				if (crdts > 18 || crdts < 12)
				{
					CurrentReqs.semcrdtError = true;
				}
				else
				{
					CurrentReqs.semcrdtError = false;
					flag = true;
					break;
				}
			}
		}
	}
}

void Registrar::Checkcoreq()
{
	vector<vector<vector<Course>>> allcrs = pSPlan->ReturnALlCrs();
	bool flag = false;
	for (int y = 0; y < 5; y++)
	{
		for (int s = 0; s < 3; s++)
		{
			for (auto ccrs : allcrs[y][s])
			{
				for (auto code : ccrs.retCoReq())
				{
					if (flag)
					{
						break;
					}
					for (auto ccrs : allcrs[y][s])
					{
						if (code != ccrs.getCode())
						{
							CurrentReqs.CoReqError = true;
						}
						else
						{
							CurrentReqs.CoReqError = false;
							break;
							flag = true;
						}
					}
				}
			}
		}
	}
}

void Registrar::Checkperq()
{
	vector<vector<vector<Course>>> allcrs = pSPlan->ReturnALlCrs();
	bool flag = false;
	for (int y = 0; y < 5; y++)
	{
		for (int s = 0; s < 3; s++)
		{
			for (auto ccrs : allcrs[y][s])
			{
				for (auto code : ccrs.retPreReq())
				{
					if (flag)
					{
						break;
					}
					for (int yi = 1; yi < y; yi++)
					{
						if (flag)
						{
							break;
						}
						for (int si = 1; si < y; si++)
						{
							if (flag)
							{
								break;
							}
							for (auto ccrs : allcrs[y-yi][s-si])
							{
								if (code != ccrs.getCode())
								{
									CurrentReqs.CoReqError = true;
								}
								else
								{
									CurrentReqs.CoReqError = false;
									break;
									flag = true;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Registrar::SetCurrentIssue()
{
	if (!(CurrentReqs.TotalCredsAchieved && CurrentReqs.UniversityCredsAchieved && CurrentReqs.TrackCredsAchieved,
		CurrentReqs.MajorCredsAchieved &&
		CurrentReqs.UniversityCoursesAchieved && CurrentReqs.MajorCoursesAchieved && CurrentReqs.TrackCoursesAchieved && CurrentReqs.CoReqError && CurrentReqs.PreqError))
		CurrentIssue = Critical;
	else if (CurrentReqs.semcrdtError)
		CurrentIssue = Moderate;

}

Registrar::Registrar()
{ 
	vector<string>mype(15, "Normal");
	mypets = mype;
	ImportRules();
	GetCourseCatalog();                     
	pGUI = new GUI;       	                     //create interface object
	pSPlan = new StudyPlan;	                    //create a study plan.
	
	Push2Stack();
}

bool Registrar::setCurrentMajor(string s)
{
	if (s == "CIE" || s == "SPC" || s == "ENV" || s == "NANENG" || s == "REE")
	{
		currentMajor = s;
		cout << currentMajor << endl;
		return true;
	}
	return false;
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
	case REPORT:
		pGUI->DisplayReport(CreateReport());
		//std::cout << pSPlan->GetTotalcrds() << "   " << RegRules.TotalCredit << endl;
		Save2File(CreateReport());
		pGUI->GetUserAction("Report saved press anywhere to continue");

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
			Course* pc = pp->ReturnCoursePointer(gInfo);
			if (pc == nullptr)
			{
				break;
			}
			else
			{
				string cotype;
				pc->setSelected(true);
				pc->DrawMe(pGUI);
				pGUI->DrawCourseDeps(pSPlan, pc);
				string pc2 = to_string(pc->getCredits());
				string title = pc->getTitle();
				string code = pc->getCode();
				coursestate courtype = pc->getstate();
				if (courtype == 0)
				{
					cotype = "Done";
				}
				if (courtype == 1)
				{
					cotype = "In Progress";
				}
				if (courtype == 2)
				{
					cotype = "Pending";
				}
				string courseinfo ="Title: " +  title + ", " + "Code: " + code + ", " + "Credits: " + pc2 + ", " + "Type: " + cotype ;
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

	case EDITTYPE:
		RequiredAction = new ActionCoursetype(this);
		break;

	case REDO:
		RedoF();
		break;

	case NOTES :
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
	while (true)
	{
		pGUI->PrintMsg("Please select the desired Major :( CIE , ENV, NANENG, REE , SPC )");
		string choice = pGUI->GetSrting();    
		if (choice == "")               //will terminate the problem if the user cancels
		{
			running = false;
			break;
		}
		if (setCurrentMajor(choice))
			break;
	}
	ImportRules();
	GetCourseCatalog();
	UpdateInterface();
	while (running)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		studentlvl();
		petition();
		UpdateInterface();
		pGUI->pet(mypets);
		pGUI->DrawTotalGPA(pSPlan->GetTotalGPA());

		Action* pAct = CreateRequiredAction();

		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))   //if action is not cancelled
			{
				pSPlan->CGPA();
				Checkcrdts();
				Checkperq();
				Checkcoreq();
				Push2Stack();
				CheckRules();
				SetCurrentIssue();
				
				while (! RedoS.empty())
				{
					RedoS.pop();
				}
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

void Registrar::Save2File(vector<vector<string>> s, string filename) const
{
	ofstream myfile;
	myfile.open("Saves\\" + filename + ".txt");
	for (auto x : s)
		myfile << x[0]+":"+x[1] << endl;
	myfile.close();
}

vector<vector<string>> Registrar::CreateReport() const
{
	vector<vector<string>> Report
	{
	 {"Total Credits Achieved",CurrentReqs.TotalCredsAchieved ? "True" : "False"},
	 {"University Credits Achieved", CurrentReqs.UniversityCredsAchieved ? "True" : "False"},
	 {"Track Credits Achieved", CurrentReqs.TrackCredsAchieved ? "True" : "False"},
	 {"Major Credit sAchieved", CurrentReqs.MajorCredsAchieved ? "True" : "False"},
	 {"University Courses Achieved", CurrentReqs.UniversityCoursesAchieved ? "True" : "False"},
	 {"Major Courses Achieved", CurrentReqs.MajorCoursesAchieved ? "True" : "False"},
	 {"Track Courses Achieved",  CurrentReqs.TrackCoursesAchieved ? "True" : "False"},
	 {"Student Level", studlvl},
	};
	return Report;
}



void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items      //test
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}


void Registrar::GetCourseCatalog()
{
	string file_name = "Catalog - 2020 12 19 .txt";
	vector<vector<string>> Words;
	string Line;
	ifstream Myfile("Rules\\" + file_name);
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
		if ( w[3] != "")
		{
             string sup= w[3].substr(7, w[3].size());
			 stringstream req(sup);
			 string halfcode;
			 string xcode="";

			 //cout << "crc : ";
			 while (getline(req, halfcode, ' '))
			 {

				 if (halfcode == "And")
				 {
					 xcode = xcode.substr(0, xcode.size() - 1);
					 //cout << xcode << "//";
					 c.CoReqList.push_back(xcode);
					 xcode = "";
				 }
				 else
				 {
					 xcode += halfcode+' ';
				 }
			 }
			 xcode = xcode.substr(0, xcode.size() - 1);
			 //cout << xcode << "//";
			 c.CoReqList.push_back(xcode); 
			 //cout << "End"<<endl;
		}
		if (w.size()==5)
		{
			//cout << "prc : ";
			string sup = w[4].substr(8, w[4].size());
			stringstream req(sup);
			string halfcode;
			string xcode = "";
			while (getline(req, halfcode, ' '))
			{
				
				if (halfcode == "And")
				{
					xcode = xcode.substr(0, xcode.size() - 1);
					//cout << xcode <<"//";
					c.PreReqList.push_back(xcode);
					xcode = "";
				}
				else
				{
					xcode += halfcode + ' ';
				}
			}
			xcode = xcode.substr(0, xcode.size() - 1);
			//cout << xcode << "//";
			c.PreReqList.push_back(xcode);
			//cout << "End" << endl;
		}
	
		char s = w[2][0];
		c.Credits = s - '0';
		//c.type = w[9];
		RegRules.CourseCatalog.push_back(c);
		}


	}
}

void Registrar::ImportRules()
{
	string file_name = "Externals\\"+currentMajor+"-Requirements.txt";
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
		for (auto var : Words[6])
		{
			Course_Code x = var;
			RegRules.UnivCompulsory.push_back(x);
		}
		for (auto var : Words[7])
		{
			Course_Code x = var;
			RegRules.UnivElective.push_back(x);
		}
		for (auto var : Words[8])
		{
			Course_Code x = var;
			RegRules.TrackCompulsory.push_back(x);
		}
		for (auto var : Words[9])
		{
			Course_Code x = var;
			RegRules.MajorCompulsory.push_back(x);
		}
		for (auto var : Words[10])
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
			list<Course_Code> coreq(i.CoReqList.begin(), i.CoReqList.end());            //converting the vector into a list
			list<Course_Code> preq(i.PreReqList.begin(), i.PreReqList.end());
			pC->setCoReq(coreq);
			pC->setPreReq(preq);
			if (count(RegRules.UnivCompulsory.begin(), RegRules.UnivCompulsory.end(), code) || count(RegRules.UnivElective.begin(), RegRules.UnivElective.end(), code))
				pC->setCourseType(univ);
			else if (count(RegRules.TrackCompulsory.begin(), RegRules.TrackCompulsory.end(), code) || count(RegRules.TrackElective.begin(), RegRules.TrackElective.end(), code)) 
				pC->setCourseType(track);
			else if (count(RegRules.MajorCompulsory.begin(), RegRules.MajorCompulsory.end(), code) || count(RegRules.MajorElective.begin(), RegRules.MajorElective.end(), code))
				pC->setCourseType(major);
			else
				pC->setCourseType(minor);
			pC->set_Elective(count(RegRules.TrackElective.begin(), RegRules.TrackElective.end(), code) || count(RegRules.UnivElective.begin(), RegRules.UnivElective.end(),
				code) || count(RegRules.MajorElective.begin(), RegRules.MajorElective.end(), code));
			return pC;
			state = false;
			break;
		}
	}
	if(state)
	return nullptr;
}

string Registrar::studentlvl()
{
	auto pp = pSPlan->ReturnALlCrs();
	int crdt = 0;
	for (auto i : pp)
	{
		for (auto sem : i)
		{
			for (auto crs : sem)
			{
				coursestate pc = crs.getstate();
				if (pc == 0)
				{
					crdt += crs.getCredits();
				}
			}
		}
	}

	if (crdt < 30)
	{
		studlvl = "Fresh";
	}
	if (crdt >= 30 && crdt < 60)
	{
		studlvl = "Sophomore";
	}
	if (crdt >= 60 && crdt < 90)
	{
		studlvl = "Junior";
	}
	if (crdt >= 90)
	{
		studlvl = "Senior";
	}

	return studlvl;
}

void Registrar::petition()
{
	auto pp = pSPlan->ReturnALlCrs();
	int n = 0;
	for (auto i : pp)
	{
		for (auto sem : i)
		{
			int crdt = 0;
			for (auto crs : sem)
			{
				crdt += crs.getCredits();
			}
			if (crdt > 18)
			{
				mypets[n] = "Overload";
			}
			if (crdt < 12)
			{
				mypets[n] = "Underload";
			}
			if (crdt <= 18 && crdt >= 12)
			{
				mypets[n] = "Normal";
			}

			if (n == 2 || n == 5 || n == 8 || n == 11 || n == 14)
			{
				if (crdt > 6)
				{
					mypets[n] = "Overload";
				}
				else
					mypets[n] = "Normal";
			}
			n++;
		}
	}
}

Registrar::~Registrar()
{
	delete pGUI;
	//delete pSPlan;
}