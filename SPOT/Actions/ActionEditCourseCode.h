#pragma once
#include "Action.h"

class ActionEditCourseCode : public Action
{
public:
	ActionEditCourseCode(Registrar*);
	bool virtual Execute();
	virtual ~ActionEditCourseCode();
};