#pragma once
#include "Action.h"
//Class responsible for adding notes action
class ActionAddNote:
	public Action
{
public:
	ActionAddNote(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddNote();
};