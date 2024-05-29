#pragma once

#include "GameObject.h"
#include "Goomba.h"

#define ID_ANI_RED_GOOMBA_WALKING 5002
#define ID_ANI_RED_GOOMBA_DIE 5003
#define ID_ANI_RED_GOOMBA_WALKING_WITH_WINGS 5004
#define ID_ANI_RED_GOOMBA_JUMP_READY 5005
#define ID_ANI_RED_GOOMBA_JUMP 5006


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
