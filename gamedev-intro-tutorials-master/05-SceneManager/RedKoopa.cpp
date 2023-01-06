#include "RedKoopa.h"

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == RED_KOOPA_STATE_DIE))
	{
		isDeleted = true;
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
	float detect_x, detect_y;
	detect->GetPosition(detect_x, detect_y);
	if (this->state == RED_KOOPA_STATE_WALKING)
	{
		if (detect_y > y)
		{
			nx = -nx;
			vx = -vx;
		}
		detect->SetPosition(x + (nx > 0 ? RED_KOOPA_WALKING_BBOX_WIDTH / 2 + DETECT_SIZE / 2 : -RED_KOOPA_WALKING_BBOX_WIDTH / 2 - DETECT_SIZE / 2), y);
	}
	else if (this->state == RED_KOOPA_STATE_ROLLING)
	{
		CGame* g = CGame::GetInstance();
		float cx, cy;
		g->GetCamPos(cx, cy);
		float boundary_left, boundary_right;
		boundary_left = cx;
		boundary_right = cx + g->GetBackBufferWidth();
		if (x - RED_KOOPA_ROLLING_BBOX_WIDTH / 2 < boundary_left || x + RED_KOOPA_ROLLING_BBOX_WIDTH / 2 > boundary_right)
		{
			nx = -nx;
			vx = -vx;
		}
	}
}

void CRedKoopa::Render()
{
	int aniId = ID_ANI_RED_KOOPA_WALKING_LEFT;
	if (nx > 0)
		aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
	if (state == RED_KOOPA_STATE_ROLLING)
	{
		aniId = ID_ANI_RED_KOOPA_ROLLING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CRedKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRedKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRedKoopaDetect*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
}

void CRedKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == RED_KOOPA_STATE_WALKING)
	{
		left = x - RED_KOOPA_WALKING_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_WALKING_BBOX_HEIGHT / 2;
		right = left + RED_KOOPA_WALKING_BBOX_WIDTH;
		bottom = top + RED_KOOPA_WALKING_BBOX_HEIGHT;
	}
	else //rolling
	{
		left = x - RED_KOOPA_ROLLING_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_ROLLING_BBOX_HEIGHT / 2;
		right = left + RED_KOOPA_ROLLING_BBOX_WIDTH;
		bottom = top + RED_KOOPA_ROLLING_BBOX_HEIGHT;
	}
}

void CRedKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case RED_KOOPA_STATE_WALKING:
	{
		if (nx < 0)
			vx = -RED_KOOPA_WALKING_SPEED;
		else if (nx > 0)
			vx = RED_KOOPA_WALKING_SPEED;
		break;
	}
	case RED_KOOPA_STATE_ROLLING:
	{
		if (nx < 0)
			vx = -RED_KOOPA_ROLLING_SPEED;
		else if (nx > 0)
			vx = RED_KOOPA_ROLLING_SPEED;
		break;
	}
	}
}