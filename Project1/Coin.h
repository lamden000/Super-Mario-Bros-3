#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_FROM_BLOCK 11001

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_ESCAPE_BLOCK_SPEED_Y 0.32f
#define COIN_GRAVITY 0.001f
#define FROM_BLOCK_TIMEOUT 1000

class CCoin : public CGameObject {
protected:
	bool isFromBlock;
	DWORD timeOut=0;
public:
	CCoin(float x, float y) : CGameObject(x, y) { isFromBlock = false; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	virtual void OnNoCollision(DWORD dt);
	void EscapeBlock();
};