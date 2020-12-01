#include "Drawable.h"



Drawable::Drawable()
{
	Selected = false;
}

Drawable::~Drawable()
{
}

void Drawable::setGfxInfo(graphicsInfo g)
{
	GfxInfo = g;
}

graphicsInfo Drawable::getGfxInfo() const
{
	return GfxInfo;
}

bool Drawable::isSelected() const
{
	return Selected;
}
bool Drawable::isClicked(graphicsInfo g) const
{
	if (g.x >= GfxInfo.x && (g.x) < (GfxInfo.x + width) && g.y >= GfxInfo.y && (g.y) < (GfxInfo.y + height))
		return true;
	else
		return false;
}
void Drawable::setDim(int w, int h)
{
	width = w;
	height = h;
}
int Drawable::getDimw() const
{
	return width;
}
int Drawable::getDimh() const
{
	return height;
}

void Drawable::setSelected(bool sel)
{
	Selected = sel;
}

