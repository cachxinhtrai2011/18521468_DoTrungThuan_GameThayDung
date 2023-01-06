#include "Ground.h"

void CGround::Render()
{
	//CAnimations* animations = CAnimations::GetInstance();
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - w / 2;
	t = y - h / 2;
	r = l + w;
	b = t + h;
}