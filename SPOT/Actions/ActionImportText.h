#pragma once
#include "Action.h"
#include <vector>
#include <string>
using namespace std;
class ActionImportText    :public Action
{
public:
	ActionImportText(Registrar*);
	bool virtual Execute();

	virtual ~ActionImportText();
	
};

