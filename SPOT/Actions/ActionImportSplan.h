#pragma once
#include "Action.h"
#include <vector>
#include <string>
using namespace std;
class ActionImportSplan    :public Action
{
public:
	ActionImportSplan(Registrar*);
	bool virtual Execute();

	virtual ~ActionImportSplan();
	
};

