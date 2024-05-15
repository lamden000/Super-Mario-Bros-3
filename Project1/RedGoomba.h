#pragma once

#include "GameObject.h"
#include "Goomba.h"

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

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_JUMP_READY 300
#define GOOMBA_STATE_JUMP 301

#define ID_ANI_GOOMBA_WALKING 5002
#define ID_ANI_GOOMBA_DIE 5003
#define ID_ANI_GOOMBA_WALKING_WITH_WINGS 5004
#define ID_ANI_GOOMBA_JUMP_READY 5005
#define ID_ANI_GOOMBA_JUMP 5006


class CRedGoomba : public CGoomba
{
protected:
	bool isOnPlatform = false;

	ULONGLONG jump_start = 0;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CRedGoomba(float x, float y, int level);
	virtual void Hop();
	virtual void ChasePlayer();
	virtual void SetState(int state);
};
