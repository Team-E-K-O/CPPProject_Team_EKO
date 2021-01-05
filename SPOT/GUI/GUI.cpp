#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include "../StudyPlan/StudyPlan.h"
#include <string>
#include <sstream>


void GUI::HighLightCLK(int i) const
{
	pWind->SetPen(HiColor, 2);
	pWind->DrawRectangle(i * MenuItemWidth, 0, i * MenuItemWidth+ MenuItemWidth, MenuBarHeight, FRAME, MenuItemWidth / 7, MenuItemWidth / 7);

}

GUI::GUI()
{ 
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	//ClearDrawingArea();    //test
	ClearStatusBar();
	ClearNotesArea();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, DrawingAreaWidth, WindHeight -StatusBarHeight);

}


void GUI::ClearNotesArea() const
{
	pWind->SetBrush(NotesBarColor);
	pWind->SetPen(OutlineColor);
	pWind->DrawRectangle(DrawingAreaWidth, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

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
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_add_course.jpeg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_DELETE]= "GUI\\Images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_UNDO]= "GUI\\Images\\Menu\\Menu_Undo.jpg";
	MenuItemImages[ITM_LOAD]= "GUI\\Images\\Menu\\Menu_Open.jpg";
	MenuItemImages[ITM_SAVE] = "GUI\\Images\\Menu\\Menu_Save.jpg";
	MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\Menu_Redo.jpg";
	MenuItemImages[ITM_MOVE] = "GUI\\Images\\Menu\\Menu_Move.jpg";
	MenuItemImages[ITM_EDIT] = "GUI\\Images\\Menu\\Item_Edit.jpg";
	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}
void GUI::RedrawCourse(AcademicYear* yr,Course* crs,int sem,int n1)
{
	graphicsInfo g = yr->getGfxInfo();
	crs->setDim(CRS_WIDTH, CRS_HEIGHT);
	int n = yr->GetNumCourses(sem);
	int space = ((WindHeight - (MenuBarHeight + 30 + StatusBarHeight)) - n * CRS_HEIGHT) / (n + 1);
	g.y = MenuBarHeight + 30 + (n1+1)*space +  n1* crs->getDimh();
	g.x = g.x + sem * yr->getDimw() / 3;
	crs->setGfxInfo(g);
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
	pWind->SetFont(20, BOLD , BY_NAME, "Times New Roman");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	//ClearDrawingArea();      //test
	ClearNotesArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

void GUI::DrawCourseDeps(StudyPlan* st, Course* thisCrs)
{
	pWind->SetPen(CoreqColor);
	pWind->SetBrush(CoreqColor);
	for (Course_Code code : thisCrs->retCoReq())
	{
		Course* thatcrs = st->ReturnCoursePointer(code);
		if (thatcrs)
		{
			pWind->DrawCircle(thisCrs->getGfxInfo().x + CRS_WIDTH, thisCrs->getGfxInfo().y + CRS_HEIGHT / 2, 4);
			pWind->DrawCircle(thatcrs->getGfxInfo().x, thatcrs->getGfxInfo().y + CRS_HEIGHT / 2, 4);
			DrawThickLine(thisCrs->getGfxInfo().x + CRS_WIDTH, thisCrs->getGfxInfo().y + CRS_HEIGHT / 2, thatcrs->getGfxInfo().x, thatcrs->getGfxInfo().y + CRS_HEIGHT / 2, 3);
		}
	}
	pWind->SetPen(PrereqColor);
	pWind->SetBrush(PrereqColor);
	for (Course_Code code : thisCrs->retPreReq())
	{
		Course* thatcrs = st->ReturnCoursePointer(code);
		if (thatcrs)
		{
			pWind->DrawCircle(thisCrs->getGfxInfo().x , thisCrs->getGfxInfo().y + CRS_HEIGHT / 2, 4);
			pWind->DrawCircle(thatcrs->getGfxInfo().x + CRS_WIDTH, thatcrs->getGfxInfo().y + CRS_HEIGHT / 2, 4);
			DrawThickLine(thisCrs->getGfxInfo().x, thisCrs->getGfxInfo().y + CRS_HEIGHT / 2, thatcrs->getGfxInfo().x + CRS_WIDTH, thatcrs->getGfxInfo().y + CRS_HEIGHT / 2, 3);
		}
	}
}

void GUI::DrawThickLine(int x1, int y1, int x2 , int y2	, int width)
{
	for (int i = 0; i < width; i++)
	{
		pWind->DrawLine(x1, y1+i, x2, y2+i);
		pWind->DrawLine(x1, y1 - i, x2, y2 - i);
	}
}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawNotes(vector<string> s) const  
{
	pWind->SetFont(CRS_HEIGHT * 0.4, PLAIN, BY_NAME, "Lucida Handwriting");  //tested ---> 17 char max for current settings
	pWind->SetPen(MsgColor);
	pWind->SetBrush(NotesBarColor);
	pWind->SetPen(OutlineColor);
	for (int i = 0; i < s.size(); i++)
		pWind->DrawString(DrawingAreaWidth + 10, MenuBarHeight + (1 + i) * 15, s[i]);

}
void GUI::DrawCourse( Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
		pWind->SetPen(DrawColor, 2);
	if (pCrs->retError())
		pWind->SetBrush(ErrorColor);
	else 
		pWind->SetBrush(FillColor);
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT,FILLED , CRS_HEIGHT/7, CRS_HEIGHT/7);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.08;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.1;
	pWind->SetFont(CRS_HEIGHT * 0.37, BOLD , BY_NAME, "Lucida Sans");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd<< "crd: " << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}

void GUI::DrawAcademicYear( AcademicYear* pY) 
{
	///TODO: compelete this function to:
	  
	    graphicsInfo gInfo = pY->getGfxInfo();    
		pY->setDim(DrawingAreaWidth / 5, DrawingAreaHeigth);
		int x1, x2;
		if (gInfo.y == 1)     //initialising the year dimensions for the first time
		{
			x1 = gInfo.x * DrawingAreaWidth / 5;
			x2 = (1 + gInfo.x) * DrawingAreaWidth / 5;
			gInfo.x = x1;
			gInfo.y = MenuBarHeight; 
			pY->setGfxInfo(gInfo);
		}
		else
		{
			x1 = gInfo.x;
			x2 =gInfo.x+ DrawingAreaWidth / 5;
		}
		string yrname = "                  YEAR    "  + to_string(pY->GetYearNumber());
		pWind->SetFont(18, BOLD, BY_NAME , "Arial Black");
		pWind->SetPen(OutlineColor);
		pWind->SetBrush(YearFill);
		pWind->DrawRectangle(x1 ,MenuBarHeight ,x2 , WindHeight - StatusBarHeight);
		pWind->DrawString(x1 + 10, MenuBarHeight + 9, yrname);
		//2 - Draw a sub - rectangle for each semester
		
		for (int n = FALL; n < SEM_CNT; n++)
		{
			string SEM_S[] = { "  FALL","SPRING","SUMMER" };
			pWind->SetFont(14, BOLD, BY_NAME , "Arial");
			pWind->SetPen(OutlineColor);
			pWind->SetBrush(SemFill);
			pWind->DrawRectangle(x1+n*(x2-x1)/3, MenuBarHeight + 30  , x1 + (n + 1) * (x2 - x1) /3, WindHeight - StatusBarHeight );
			pWind->DrawString(x1 + n * (x2 - x1) / 3 + 15, MenuBarHeight + 35, SEM_S[n]);
		}
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
				HighLightCLK(ClickedItemOrder);
				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_EXIT: return ActionData{ EXIT };		//Exit
				case ITM_DELETE: return ActionData{ DEL_CRS }; 
				case ITM_UNDO:return ActionData{ UNDO };
				case ITM_REDO:return ActionData{ REDO };
				case ITM_LOAD:return ActionData{ LOAD };
				case ITM_SAVE:return ActionData{ SAVE };
				case ITM_MOVE:return ActionData{ MOVE };
				case ITM_EDIT:return ActionData{ EDIT };

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight && x<DrawingAreaWidth)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}
			//[3] User clicks on the notes area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight && x >= DrawingAreaWidth)
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
