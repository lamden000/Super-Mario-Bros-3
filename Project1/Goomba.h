#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_ACEL_X 0.0001f
#define GOOMBA_JUMP_SPEED 0.45f
#define GOOMBA_JUMP_READY_SPEED 0.15f
#define GOOMBA_JUMP_COOLDOWN 1300
#define GOOMBA_JUMP_READY_TIME 900


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_LEVEL_NORMAL 1
#define GOOMBA_LEVEL_WINGS 2

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_JUMP_READY 300
#define GOOMBA_STATE_JUMP 301

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define GOOMBA_SCALEX 0.35f
#define  GOOMBA_SCALEY 0.35f

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int level;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return  state != GOOMBA_STATE_DIE; };
	virtual int IsBlocking() { return state!=GOOMBA_STATE_DIE; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoomba(float x, float y, int level = 1);
	virtual void DecreaseLevel();
	virtual void SetState(int state);
};