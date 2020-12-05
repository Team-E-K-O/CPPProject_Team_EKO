#pragma once
#include <list>

#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"


//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits = 0, TotalMajorCredits = 0,
		TotalTrackCredits = 0, TotalConcentrationCredits = 0,
		TotalMinorCredits = 0, YearNumber; 
	int NumberOfCourses[SEM_CNT];

	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	
public:
	AcademicYear();
	virtual ~AcademicYear();
	int GetYearNumber() const;
	void SetYearNumber(int);
	bool AddCourse(Course*, SEMESTER );
	int GetNumCourses(int) const;
	void virtual DrawMe(GUI*) ;
	virtual Course* ReturnCoursePointer(graphicsInfo, SEMESTER sem);

	void DeleteCourse(graphicsInfo,SEMESTER sem);
	Course* SaveCourse(SEMESTER sem);

};

