#pragma once
#include "Action.h"
class ActionModifyGrade :
    public Action
{
public:
    ActionModifyGrade(Registrar*);
    bool virtual Execute();
    virtual ~ActionModifyGrade();
};

