#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
#include <stack>


//The maestro class for the application
class Registrar
{
	stack<StudyPlan> UndoS, RedoS;
	StudyPlan PlanTemp;
	bool running ;
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
public:
	Registrar();
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
	void UndoF();
	void RedoF();
	~Registrar();
};

