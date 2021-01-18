#pragma once
#include "Action.h"
//Class responsible for adding course action
class ActionCoursetype :
	public Action
{
public:
	ActionCoursetype(Registrar*);
	bool virtual Execute();
	virtual ~ActionCoursetype();
}; 
