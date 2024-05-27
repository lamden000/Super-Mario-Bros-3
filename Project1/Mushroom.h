#pragma once
#include "Gameobject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.04f
#define MUSHROOM_ESCAPE_BLOCK_SPEED 0.3f

#define MUSHROOM_BBOX_WIDTH 13
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_DIE_TIMEOUT 500
#define MUSHROOM_TYPE_RED 1
#define MUSHROOM_TYPE_GREEN 2

#define ID_ANI_RED_MUSHROOM 2224
#define ID_ANI_GREEN_MUSHROOM 2225

class CMushroom :public CGameObject {

protected:
	float ay;
	int type;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	void EscapeBlock();
	CMushroom(float x, float y,int type=1);
	int GetType() { return type; }
};
