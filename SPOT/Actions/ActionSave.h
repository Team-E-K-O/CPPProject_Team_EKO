#pragma once
#include "Action.h"

class ActionSave :
	public Action
{
public:
	ActionSave(Registrar*);
	bool virtual Execute();
	virtual ~ActionSave();
};