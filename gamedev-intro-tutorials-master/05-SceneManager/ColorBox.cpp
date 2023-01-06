#include "ColorBox.h"

void CColorBox::Render()
{
	//CAnimations* animations = CAnimations::GetInstance();
	RenderBoundingBox();
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - w / 2;
	t = y - h / 2;
	r = l + w;
	b = t + h;
}