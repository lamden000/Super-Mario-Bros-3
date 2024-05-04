#pragma once
#include "GameObject.h"

#define BUSH_ANIID_TYPE_1_LEFT 20261
#define BUSH_ANIID_TYPE_2_LEFT 20271
#define BUSH_ANIID_TYPE_3_LEFT 20281
#define BUSH_DIRECTION_LEFT 0
#define BUSH_DIRECTION_RIGHT 1
#define BUSH_SCALEX 0.7
#define BUSH_SCALEY 0.7

class CBush : public CGameObject
{
protected:
	int type;
	int direction;
public:
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CBush(float x, float y,int type, int direction=1);
};

