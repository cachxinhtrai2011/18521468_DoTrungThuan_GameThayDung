#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CGround : public CGameObject {
	int w;
	int h;
public:
	CGround(float x, float y, int w, int h) : CGameObject(x, y)
	{
		this->w = w;
		this->h = h;
	}
	void Render();
	int IsBlocking() { return 1; }
	int IsCollidable() { return 0; };
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

