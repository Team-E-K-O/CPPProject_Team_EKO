#include "ActionImportText.h"
#include <iostream>
#include <fstream>
#include "..\Registrar.h"

ActionImportText::ActionImportText(Registrar* p) : Action(p)
{
}
bool ActionImportText::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Enter the name or the path of the study plan file :");
	string file_name = pGUI->GetSrting();
	vector<string> Lines;
	string Line;
	ifstream Myfile(file_name);
	if (!Myfile.is_open())
		return false;
	else
	{

		while (getline(Myfile,Line))
		{
			Lines.push_back(Line);
		}
		Myfile.close();
		string word = "";
		for (string y : Lines)
		{
			vector<string> words;
			string word = "";
			for (auto x : y)
			{
				if (x == ',')	
					word = "";
				else 
					word = word + x;
			}
			words.push_back(word);
			////code for adding courses per sem.
			string years = words[0];
			int yr = years[5] - 48;


		}
   }
}
ActionImportText::~ActionImportText()
{

}