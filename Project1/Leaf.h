#pragma once
#include "GameObject.h"

#define ANIID 20241
#define LEAF_WIDTH 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16
#define LEAF_SPEEDY 0.13f

class CLeaf : public CGameObject
{
protected:
	void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CLeaf(float x, float y);
};


