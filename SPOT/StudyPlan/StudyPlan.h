#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
//#include <iostream>   //debug_e
using namespace std;
//A full study plan for a student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*> plan;	//plan is a list of academic years
	vector<string>Notes;       //lines of notes


	string PlanNotes;

public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	Course* ReturnCoursePointer(graphicsInfo g);      // return course by location
	Course* ReturnCoursePointer(Course_Code);                                 //return course by code
	void virtual DrawMe(GUI*);
	void DetYearSem(graphicsInfo g, int& year, SEMESTER& Sem);
	void AddPlanNote(string);
	virtual ~StudyPlan();
	void DeleteALL();            //wipes all courses
	vector<vector<vector<Course>>>  ReturnALlCrs() const;     //returns a map of all courses in their places
	void StaticCopyit(StudyPlan*);
	void  DeleteCrs(graphicsInfo);
	int GetTotalcrds() const;
	int GetMajorcrds() const;
	int GetUnivcrds() const;
	int GetConccrds() const;
	int GetMinorcrds() const;
	int GetTrackcrds() const;
};

