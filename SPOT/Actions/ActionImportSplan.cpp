#include "ActionImportSplan.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "..\Registrar.h"

ActionImportSplan::ActionImportSplan(Registrar* p) : Action(p)
{
}
bool ActionImportSplan::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Enter the name or the path of the study plan file :");
	string file_name = pGUI->GetSrting();
	vector<vector<string>> Words;
	string Line;
	ifstream Myfile("Saves\\" + file_name + ".txt");
	if (!Myfile.is_open())
		return false;
	else
	{
		StudyPlan* pS = pReg->getStudyPlay();
		pS->DeleteALL();
		while (getline(Myfile, Line))
		{
			stringstream ssLine(Line);
			string Word;
			vector<string> linewrds;
			while (getline(ssLine, Word, ','))
				linewrds.push_back(Word);
			Words.push_back(linewrds);
		}
		for (auto i :Words)
		{
			string yr = i[0];
			string sm = i[1];
			int year = yr[5] - '0';
			SEMESTER sem;
			if (sm == "Fall")
				sem = FALL;
			if (sm == "Spring")
				sem = SPRING;
			if (sm == "Summer")
				sem = SUMMER;
			for (int w=2;w<i.size();w++)
			{
				Course_Code code = i[w];
				string Title = "Test101";
				int crd = 0;
				Course* pC = new Course(code, Title, crd);
				
				pS->AddCourse(pC, year, sem);
			}
		}
		Myfile.close();
		return true;

	}
   
}
ActionImportSplan::~ActionImportSplan()
{

}