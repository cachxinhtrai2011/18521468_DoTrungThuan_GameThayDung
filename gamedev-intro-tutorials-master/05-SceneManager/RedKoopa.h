#pragma once

#include "RedKoopaDetect.h"
#define RED_KOOPA_STATE_WALKING			1
#define RED_KOOPA_STATE_ROLLING			2
#define RED_KOOPA_STATE_DIE	    		3

#define RED_KOOPA_WALKING_BBOX_WIDTH	    	16
#define RED_KOOPA_WALKING_BBOX_HEIGHT    		26
#define RED_KOOPA_ROLLING_BBOX_WIDTH	16
#define RED_KOOPA_ROLLING_BBOX_HEIGHT   18

#define ID_ANI_RED_KOOPA_WALKING_LEFT 1701
#define ID_ANI_RED_KOOPA_WALKING_RIGHT 1702
#define ID_ANI_RED_KOOPA_ROLLING 1703

#define RED_KOOPA_WALKING_SPEED 0.03f
#define RED_KOOPA_ROLLING_SPEED 0.05f
class CRedKoopa : public CGameObject
{
protected:
    float ax;
    float ay;
    LPGAMEOBJECT detect;
public:
    CRedKoopa(float x, float y, LPGAMEOBJECT detect) : CGameObject(x, y) {
        SetState(RED_KOOPA_STATE_WALKING);
        this->ax = 0;
        this->ay = DETECT_GRAVITY;
        this->detect = detect;
        this->nx = 1;
    };
    void SetDetectObject(LPGAMEOBJECT detect) { this->detect = detect; }
    virtual void SetState(int state);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};