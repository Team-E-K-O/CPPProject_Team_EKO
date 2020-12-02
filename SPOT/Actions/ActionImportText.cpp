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

		while (getline(Myfile,Line))
		{
			Lines.push_back(Line);
		}
		Myfile.close();


}
ActionImportText::~ActionImportText()
{

}