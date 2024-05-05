#pragma once
#include "GameObject.h"

#define ANIID 20241
#define LEAF_WIDTH 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16
#define LEAF_GRAVITY 0.0001f
#define LEAF_ACCEL_X 0.00015f
#define LEAF_ESCAPE_BLOCK_SPEED_Y 0.08f
#define LEAF_DROP_VY_MAX 0.035f
#define LEAF_JUMP_TIME 600
#define LEAF_FLUCTUATION_RATE 15

class CLeaf : public CGameObject
{
protected:
	float axis;
	float ax;
	float ay;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	void OnNoCollision(DWORD dt);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void EscapeBlock();
	CLeaf(float x, float y);
};


