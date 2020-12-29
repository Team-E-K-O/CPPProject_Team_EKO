#pragma once
#include <string>
using namespace std;

#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include <vector>

class Course;
class AcademicYear;
//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course
		ITM_DELETE,
		ITM_MOVE,
		ITM_EDIT,
		ITM_UNDO,
		ITM_REDO,
		ITM_LOAD,
		ITM_SAVE,
		
						//TODO: Add more items names here

         
		ITM_EXIT,		//Exit item

		ITM_CNT			//no. of menu items ==> This should be the last line in this enum

	};

	//Some constants for GUI
	static const int	WindWidth = 1300, WindHeight = 700,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 60,	//Status Bar Height
		MenuBarHeight = 80,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		DrawingAreaWidth = 1080, MenuItemWidth = 80,	    //Width of each item in the menu
		DrawingAreaHeigth = WindHeight - StatusBarHeight - MenuBarHeight;



	color DrawColor = BLACK;		//Drawing color
	color FillColor = LIGHTCYAN;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLACK;			//Messages color
	color BkGrndColor = SKYBLUE;	//Background color
	color StatusBarColor = ANTIQUEWHITE;//StatusBar color
	color NotesBarColor =LEMONCHIFFON;     //NotesBar color
	color OutlineColor = BLACK;     //Outline color for all rectangles
	color YearFill = FLORALWHITE;    //Year Recangle Box
	color SemFill = SNOW;
		

	string WindTitle = "Team E_K_O";
	window* pWind;
	
public:
	GUI();
	void RedrawCourse(AcademicYear* , Course* , int ,int );
	void CreateMenu() const;
	void HighLightCLK(int) const ;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar
	void DrawNotes(vector<string>) const;     //Clears the notes bar
	void ClearNotesArea() const;
	//output functions
	void PrintMsg(string) const;		//prints a message on status bar
	//Drawing functions
	void DrawCourse( Course* );
	void DrawAcademicYear( AcademicYear*);
	void UpdateInterface() const;
	
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	string GetSrting() const;


	
	

	~GUI();
};

