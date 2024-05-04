#pragma once
#include "GameObject.h"

#define BROWNKOOPAS_GRAVITY 0.002f
#define BROWNKOOPAS_WALKING_SPEED 0.05f
#define BROWNKOOPAS_LEVEL_BIG 2
#define BROWNKOOPAS_LEVEL_SMALL 1

#define BROWNKOOPAS_BBOX_WIDTH 16
#define BROWNKOOPAS_BBOX_HEIGHT 14
#define BROWNKOOPAS_BBOX_HEIGHT_DIE 7

#define BROWNKOOPAS_STATE_WALKING 100
#define BROWNKOOPAS_STATE_SHELL 300

#define ID_ANI_SMALL_BROWNKOOPAS_WALKING_RIGHT 11
#define ID_ANI_SMALL_BROWNKOOPAS_WALKING_LEFT 12
#define ID_ANI_SMALL_BROWNKOOPAS_HIDING 13
#define ID_ANI_SMALL_BROWNKOOPAS_SHELL 14

#define ID_ANI_BIG_BROWNKOOPAS_WALKING_RIGHT 30
#define ID_ANI_BIG_BROWNKOOPAS_WALKING_LEFT 31
#define ID_ANI_BIG_BROWNKOOPAS_SHELL 32

#define BROWNKOOPAS_REVIVE_TIME  4000

class CBrownKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	int level;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBrownKoopas(float x, float y, int level);
	virtual void SetState(int state);
};


