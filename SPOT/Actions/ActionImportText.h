#pragma once
#include "Action.h"
#include <vector>
#include <string>
class ActionImportText    :public Action
{
public:
	ActionImportText(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportText();
	vector<string> 
};

