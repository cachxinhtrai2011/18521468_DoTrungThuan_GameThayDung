#pragma once
#include "GameObject.h"
class CColorBox :public CGameObject
{
private:
	int w;
	int h;
public:
	CColorBox(float x, float y, int w, int h) :CGameObject(x, y) {
		this->w = w;
		this->h = h;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 0; };
	int IsBlocking() { return 2; }
};