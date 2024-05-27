#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_BOUNCING_SPEED 0.15f;
#define BROWNKOOPAS_GRAVITY 0.002f;

#define BROWNKOOPAS_BBOX_WIDTH 10
#define BROWNKOOPAS_BBOX_HEIGHT 23
#define BROWNKOOPAS_BBOX_HEIGHT_SHELL 11


#define BROWNKOOPAS_LEVEL_NORMAL 1
#define BROWNKOOPAS_LEVEL_WINGS 2

#define BROWNKOOPAS_STATE_WALKING 100
#define BROWNKOOPAS_STATE_REVIVING 200
#define KOOPAS_STATE_SHELL 300
#define BROWNKOOPAS_STATE_SHELL_BOUNCING 400

#define ID_ANI_BROWNKOOPAS_WALKING_RIGHT 12
#define ID_ANI_BROWNKOOPAS_WALKING_RIGHT_WITH_WINGS 18
#define ID_ANI_BROWNKOOPAS_JUMP_RIGHT 19
#define ID_ANI_BROWNKOOPAS_WALKING_LEFT 11
#define ID_ANI_BROWNKOOPAS_WALKING_LEFT_WITH_WINGS 17
#define ID_ANI_BROWNKOOPAS_JUMP_RIGHT 20
#define ID_ANI_BROWNKOOPAS_REVIVING 13
#define ID_ANI_BROWNKOOPAS_SHELL 14
#define ID_ANI_BROWNKOOPAS_SHELL_BOUNCING 15

#define BROWNKOOPAS_SHELL_TIME  4000
#define BROWNKOOPAS_REVIVE_TIME  2000

#define BROWKOOPAS_SCALEX 0.35f
#define BROWKOOPAS_SCALEY 0.35f

class CBrownKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	int level;
	bool steppedBack = false;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);

public:
	CBrownKoopas(float x, float y,int level);
	virtual void DecreaseLevel();
	virtual void SetState(int state,float nx=0);
};


