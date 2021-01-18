#pragma once
#include <string>
#include <list>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"


enum coursestate
{
	done,
	inprogress,
	pending
};

//Base class for all types of courses
class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	bool Has_Error=false;
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
	coursestate courtype = done;
public:
	Course(Course_Code r_code,string r_title, int crd);
	string getTitle() const;
	string getCode() const;
	coursestate gettype();
	void settype(string n);
	int getCredits() const;
	void setPreReq(list<Course_Code>);
	void setCoReq(list<Course_Code>);
	list<Course_Code> retPreReq() const;
	list<Course_Code> retCoReq() const;
	void setError(bool);
	bool retError() const;
	void DrawMe(GUI*) ;
	virtual ~Course();
};
