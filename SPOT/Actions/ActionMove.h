#pragma once
#include "Action.h"

class ActionMove : public Action
{
public : 
	ActionMove(Registrar*);
	bool virtual Execute();
	virtual ~ActionMove();
};