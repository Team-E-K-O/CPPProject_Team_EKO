#pragma once
#include <string>
#include <list>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"

//Base class for all types of courses

enum crsgrades
{
	F, CP, C, CM, BP, B, BM, AM, A
};

inline double lettertograde(crsgrades g)
{
	if (g == F)
	{
		return 0.0;
	}

	if (g == CM)
	{
		return 1.67;
	}

	if (g == C)
	{
		return 2;
	}

	if (g == CP)
	{
		return 2.33;
	}

	if (g == BM)
	{
		return 2.67;
	}

	if (g == B)
	{
		return 3;
	}

	if (g == BP)
	{
		return 3.33;
	}

	if (g == AM)
	{
		return 3.67;
	}

	if (g == A)
	{
		return 4;
	}
}

class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	crsgrades Grade;        //Grade
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	bool Has_Error=false;
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
public:
	Course(Course_Code r_code,string r_title, int crd);
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	crsgrades getGrade() const;
	void setPreReq(list<Course_Code>);
	void setCoReq(list<Course_Code>);
	list<Course_Code> retPreReq() const;
	list<Course_Code> retCoReq() const;
	void setError(bool);
	bool retError() const;
	void DrawMe(GUI*) ;
	virtual ~Course();

};
