#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <string>
#include <sstream>
#include <iostream>    //debug_e

GUI::GUI()
{ 
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	ClearNotesBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, DrawingAreaWidth, WindHeight -StatusBarHeight);

}

void GUI::ClearNotesBar() const
{
	pWind->SetBrush(NotesBarColor);
	pWind->SetPen(OutlineColor);
	pWind->DrawRectangle(1300, MenuBarHeight, DrawingAreaWidth, WindHeight - StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_add_course.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_DELETE]= "GUI\\Images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_UNDO]= "GUI\\Images\\Menu\\Menu_Undo.jpg";
	MenuItemImages[ITM_OPEN]= "GUI\\Images\\Menu\\Menu_Open.jpg";
	MenuItemImages[ITM_SAVE] = "GUI\\Images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\Menu_Redo.jpg";
	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//Prints a message on the notes bar
void GUI::PrintNote(string msg,int x,int y) const
{
	// Print the Message
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(x, y, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	ClearNotesBar();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD , BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd<< "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	///TODO: compelete this function to:
	   graphicsInfo gInfo = pY->getGfxInfo();
	   int x1 = gInfo.x * DrawingAreaWidth / 5;
	   int x2 = (1 + gInfo.x) * DrawingAreaWidth / 5;
		string yrname = "YEAR " + to_string(gInfo.x + 1);
		pWind->SetPen(OutlineColor);
		pWind->SetBrush(YearFill);
		pWind->DrawRectangle(x1 ,MenuBarHeight ,x2 , WindHeight - StatusBarHeight);
		pWind->DrawString(x1 + 10, MenuBarHeight + 15, yrname);
		//2 - Draw a sub - rectangle for each semester
		
		for (int n = FALL; n < SEM_CNT; n++)
		{
			string SEM_S[] = { "FALL","SPRING","SUMMER" };
			pWind->SetPen(OutlineColor);
			pWind->SetBrush(YearFill);
			pWind->DrawRectangle(x1+n*(x2-x1)/3, MenuBarHeight + 30  , x1 + (n + 1) * (x2 - x1) /3, WindHeight - StatusBarHeight );
			pWind->DrawString(x1 + n * (x2 - x1) / 3 + 15, MenuBarHeight + 35, SEM_S[n]);
		}
	
	//		
	//Then each course should be drawn inside rect of its year/sem
	
}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);
		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}

		
		if (ctInput == LEFT_CLICK)	//mouse left click
			
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check which Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_EXIT: return ActionData{ EXIT };		//Exit
				case ITM_DELETE: return ActionData{ DEL_CRS }; 
				case ITM_UNDO:return ActionData{ UNDO };
				case ITM_REDO:return ActionData{ REDO };
				case ITM_OPEN:return ActionData{ OPEN };
				case ITM_SAVE:return ActionData{ SAVE };

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight && x<1000)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}
			//[3] User clicks on the notes area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight && x >= 1000)
			{
				return ActionData{ NOTES_AREA,x,y };	//user want clicks inside notes area
			}

			//[4] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar

	

	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}








GUI::~GUI()
{
	delete pWind;
}
