#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "ActionSave.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

ActionSave::ActionSave(Registrar* p) :Action(p)
{
}

bool ActionSave::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Write the name of the .txt file: ");

	string filename = pGUI->GetSrting();
	StudyPlan* pp = pReg->getStudyPlan();
	ofstream myfile;
	myfile.open("Saves\\" + filename + ".txt");
	 vector<vector<vector<Course>>> ff = pp->ReturnALlCrs();
	int n1=0;
	vector<string> lines;
	for (auto i : ff)
	{ 
		int n2 = 0;
		
		for (auto n : i)
		{
			string line="Year " + to_string(n1 + 1);
			if (n2 == 0)
			{
				string sem = "Fall";
				line = line + ',' + sem;
			}
			else if (n2 == 1)
			{
				string sem = "Spring";
				line = line + ',' + sem;
			}
			else if (n2 == 2)
			{
				string sem = "Summer";
				line = line + ',' + sem;
			}
			
			for (auto x : n)
			{ 
				line += ',' + x.getCode();
			}
			if(!n.empty())
			lines.push_back(line);
			n2++;
		}
		n1++;
	}
	for (auto x : lines)
		myfile<<x<<endl;
	myfile.close();
	return true;
}


ActionSave::~ActionSave()
{
}