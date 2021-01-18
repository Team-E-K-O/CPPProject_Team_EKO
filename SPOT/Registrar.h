#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
#include <stack>
#include <vector>

enum Issue
{
     None,Moderate,Critical
};
struct ProgramReqs
{
	bool TotalCredsAchieved, UniversityCredsAchieved, TrackCredsAchieved,
		MajorCredsAchieved, 
		UniversityCoursesAchieved, MajorCoursesAchieved, TrackCoursesAchieved;
};

//The maestro class for the application
class Registrar
{
	stack<StudyPlan> UndoS, RedoS;
	StudyPlan PlanTemp;
	bool running ;
	Issue CurrentIssue;
	string currentMajor;
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
	ProgramReqs CurrentReqs;
	string studlvl;
	vector<string> mypets;

public:
	Registrar();
	bool setCurrentMajor(string);
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlan() const;
	Rules ReturnRules() const;
	void GetCourseCatalog();
	void ImportRules();
	Course * CreateCourseP(Course_Code);
	void Run();
	void Push2Stack();
	void CheckRules();
	void SetCurrentIssue();
	void UndoF();
	void RedoF();
	string studentlvl();
	void petition();
	void Save2File(vector<vector<string>> ,string filename ="Report") const;
	vector<vector<string>> CreateReport() const;
	~Registrar();
};

