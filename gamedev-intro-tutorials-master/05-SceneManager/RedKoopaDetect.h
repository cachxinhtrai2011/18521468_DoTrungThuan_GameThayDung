#pragma once
#include "GameObject.h"

#define DETECT_GRAVITY	0.0008f
#define DETECT_SIZE	26

class CRedKoopaDetect :
	public CGameObject
{
public:
	CRedKoopaDetect(float x, float y) : CGameObject(x, y) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};