#pragma once
class GUI;

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x, y;	
};
//constants related to objects to be drawn
enum
{
	CRS_WIDTH = 72,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = 40,	//Height of course rectangle to be drawn on screen
	PLAN_YEAR_WIDTH = CRS_WIDTH * 3,	//width of plan year rectangle to be drawn on screen
	PLAN_YEAR_HEIGHT	//Height of play year rectangle to be drawn on screen
};

//Base class for all drawable classes
class Drawable
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	bool Selected;	//is this obj selected (to highlight when drawing)
	bool Drawed=false;
	int height;
	int width;

public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	void setSelected(bool );
	bool isSelected() const;
	bool isClicked(graphicsInfo)const;   //function to determine if this object is clicked or not
	void setDim(int w, int h);           //function to set the heigth and width for an object
	int getDimw() const;
	int getDimh() const;
	void virtual DrawMe(GUI*) = 0;
	void SetDrawed();
	bool IsDrawed() const;
	virtual ~Drawable();
};

