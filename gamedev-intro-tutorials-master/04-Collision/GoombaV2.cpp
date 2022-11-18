#include "GoombaV2.h"

CGoombaV2::CGoombaV2(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_V2_STATE_WALKING);
}

void CGoombaV2::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_V2_STATE_DIE)
	{
		left = x - GOOMBA_V2_BBOX_WIDTH/2;
		top = y - GOOMBA_V2_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_V2_BBOX_WIDTH;
		bottom = top + GOOMBA_V2_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_V2_BBOX_WIDTH/2;
		top = y - GOOMBA_V2_BBOX_HEIGHT/2;
		right = left + GOOMBA_V2_BBOX_WIDTH;
		bottom = top + GOOMBA_V2_BBOX_HEIGHT;
	}
}

void CGoombaV2::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoombaV2::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoombaV2*>(e->obj)) return;

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoombaV2::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_V2_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_V2_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoombaV2::Render()
{
	int aniId = ID_ANI_GOOMBA_V2_WALKING;
	if (state == GOOMBA_V2_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_V2_DIE;
	}
	if (state == GOOMBA_V2_STATE_IDDLE)
	{
		aniId = ID_ANI_GOOMBA_V2_IDDLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CGoombaV2::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_V2_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_V2_BBOX_HEIGHT - GOOMBA_V2_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_V2_STATE_WALKING:
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_V2_STATE_IDDLE:
			vx = 0;
			vy = 0;
			ax = 0;
			ay = 0;
			break;
	}
}
