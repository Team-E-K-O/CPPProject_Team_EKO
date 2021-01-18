#include "StudyPlan.h"
#include "../GUI/GUI.h"


StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++) {
		plan.push_back(new AcademicYear);
		graphicsInfo gfx;
		gfx.x = i;
		gfx.y = 1;
		plan[i]->setGfxInfo(gfx);
		plan[i]->SetYearNumber(i+1) ;
	}
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	//std::cout << year<<endl;    //debug_e
	plan[year - 1]->AddCourse(pC, sem);
	TotalCredits += pC->getCredits();
	if (pC->getCourseType() == univ)
		TotalUnivCredits += pC->getCredits();
	else if (pC->getCourseType() == major)
		TotalMajorCredits += pC->getCredits();
	else if (pC->getCourseType() == track)
		TotalTrackCredits += pC->getCredits();
	return true;
}
void StudyPlan::DetYearSem(graphicsInfo g, int& year, SEMESTER& Sem) 
{
	for (int i = 0; i < plan.size(); i++)
		if (plan[i]->isClicked(g))
		{
			year = i + 1;
			graphicsInfo  g1 = plan[i]->getGfxInfo();
			if (g.x < g1.x + plan[i]->getDimw() / 3)
				Sem = FALL;
			else if (g.x >= g1.x + plan[i]->getDimw() / 3 && g.x < g1.x + 2 * plan[i]->getDimw() / 3)
				Sem = SPRING;
			else
				Sem = SUMMER;
			break;
		}

}

void StudyPlan::DrawMe(GUI* pGUI)
{
	//Plan draws all year inside it
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DrawMe(pGUI);	
	}
}
void StudyPlan::AddPlanNote(string s)
{
	Notes.push_back("");
	string str="";
	int n = 0;
	for (char i :s)
	{
		str += i;
		n++;
		/*if (n==24)
		{
			Notes.push_back(str);
			n = 0;
			str = "";
		}*/
	}
	Notes.push_back(str);
}

void StudyPlan::DeleteCrs(graphicsInfo g)
{
	int year;
	SEMESTER sem ;
	DetYearSem(g, year, sem);
	TotalCredits -= ReturnCoursePointer(g)->getCredits();
	plan[year - 1]->DeleteCourse(g, sem);
}

int StudyPlan::GetTotalcrds() const
{
	return TotalCredits;
}

int StudyPlan::GetMajorcrds() const
{
	return TotalMajorCredits;
}

int StudyPlan::GetUnivcrds() const
{
	return TotalUnivCredits;
}

int StudyPlan::GetConccrds() const
{
	return TotalConcentrationCredits;
}

int StudyPlan::GetMinorcrds() const
{
	return TotalMinorCredits;
}

int StudyPlan::GetTrackcrds() const
{
	return TotalTrackCredits;
}

void StudyPlan::DeleteALL()
{
	TotalCredits = 0,
	TotalUnivCredits = 0, TotalMajorCredits = 0,
	TotalTrackCredits = 0, TotalConcentrationCredits = 0,
	TotalMinorCredits = 0;
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DeleteAll();
	}
}

Course* StudyPlan::ReturnCoursePointer(graphicsInfo g)
{
	int year;
	SEMESTER sem;
	DetYearSem(g, year, sem);
	return plan[year - 1]->ReturnCoursePointer(g, sem);
}

Course* StudyPlan::ReturnCoursePointer(Course_Code code)
{
	Course* Ccourse=nullptr;
	for (auto yr :plan)
	{
		Ccourse = yr->ReturnCoursePointer(code);
		if (Ccourse)       		// not a null pointer
			break;
	}
	return Ccourse;	
}

StudyPlan::~StudyPlan()
{
	/*for (auto x : plan)       
		delete x;*/
}

vector<vector<vector<Course>>> StudyPlan::ReturnALlCrs() const
{
	vector<vector<vector<Course>>> all;
	for (auto it : plan)
	{
	    vector<vector<Course>> x =(it)->ReturnAllCrs();
		all.push_back(x);
	}
	return all;
}

vector<string> StudyPlan::ReturnNotes() const
{
	return Notes;
}

void StudyPlan::StaticCopyit(StudyPlan* sp)
{
	plan.clear();
	int n = 0;
	//int test = 0; //debug_e
	vector<vector<vector<Course>>> temp = sp->ReturnALlCrs();
	for (auto yer : temp)
	{
		AcademicYear* tempyr=new  AcademicYear;
		int smstr = 0;
		for (auto sem : yer) {
			for (auto crs : sem)
			{
				Course* tempcrs = new Course(crs);
				tempyr->AddCourse(tempcrs,static_cast<SEMESTER>(smstr));
				//std::cout << ++test << endl;   //debug_e
			}
			smstr++;
		}
		plan.push_back(tempyr);
		graphicsInfo gfx;
		gfx.x = n;
		gfx.y = 1;
		plan[n]->setGfxInfo(gfx);
		plan[n]->SetYearNumber(n + 1);
		n++;
	}	
}
