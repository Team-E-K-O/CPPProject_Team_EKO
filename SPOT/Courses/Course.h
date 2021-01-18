#pragma once
#include <string>
#include <list>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"
enum Course_type
{
	univ ,major ,minor ,track ,conc
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
	bool Elective = false;
	Course_type c_type;
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
public:
	Course(Course_Code r_code,string r_title, int crd);
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	void set_Elective(bool);
	bool is_ELective() const;
	Course_type getCourseType() const;
	void setCourseType(Course_type);
	void setPreReq(list<Course_Code>);
	void setCoReq(list<Course_Code>);
	list<Course_Code> retPreReq() const;
	list<Course_Code> retCoReq() const;
	void setError(bool);
	bool retError() const;
	void DrawMe(GUI*) ;
	virtual ~Course();

};
