#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.0015f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_BOUNCING_SPEED 0.15f;
#define KOOPAS_ATTACKED_SPEED_X 0.05f;
#define KOOPAS_ATTACKED_SPEED_Y 0.4f;

#define BROWNKOOPAS_BBOX_WIDTH 10
#define BROWNKOOPAS_BBOX_HEIGHT 23
#define BROWNKOOPAS_BBOX_HEIGHT_SHELL 11


#define BROWNKOOPAS_LEVEL_NORMAL 1
#define BROWNKOOPAS_LEVEL_WINGS 2

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_REVIVING 200
#define KOOPAS_STATE_SHELL 300
#define KOOPAS_STATE_SHELL_BOUNCING 400

#define ID_ANI_BROWNKOOPAS_WALKING_RIGHT 12
#define ID_ANI_BROWNKOOPAS_WALKING_RIGHT_WITH_WINGS 18
#define ID_ANI_BROWNKOOPAS_JUMP_RIGHT 19
#define ID_ANI_BROWNKOOPAS_WALKING_LEFT 11
#define ID_ANI_BROWNKOOPAS_WALKING_LEFT_WITH_WINGS 17
#define ID_ANI_BROWNKOOPAS_JUMP_RIGHT 20
#define ID_ANI_BROWNKOOPAS_REVIVING 13
#define ID_ANI_BROWNKOOPAS_REVIVING_UPSIDE_DOWN 16
#define ID_ANI_BROWNKOOPAS_SHELL 14
#define ID_ANI_BROWNKOOPAS_SHELL_UPSIDE_DOWN 17
#define ID_ANI_BROWNKOOPAS_SHELL_BOUNCING 15

#define BROWNKOOPAS_SHELL_TIME  4000
#define BROWNKOOPAS_REVIVE_TIME  2000
#define KOOPAS_DIE_TIMEOUT  1000

#define BROWKOOPAS_SCALEX 0.35f
#define BROWKOOPAS_SCALEY 0.35f

class CBrownKoopas : public CGameObject
{
protected:
	float start_x;
	float start_y;
	float start_level;
	float ax;
	float ay;
	int level;
	bool isHolded;
	bool isUpsideDown;
	bool isDead;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithQestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);

public:
	CBrownKoopas(float x, float y,int level);
	virtual void DecreaseLevel();
	virtual void SetIsHolded(bool isHolded) { this->isHolded = isHolded; }
	virtual void SetState(int state,float nx=-1);
	virtual bool Respawn();
	virtual int IsBlocking() { return !isHolded&& !isDead; }
	virtual int IsCollidable() { return !isDead; }
	virtual void DropCollision();
	virtual void GetAttacked(int nx);
};


