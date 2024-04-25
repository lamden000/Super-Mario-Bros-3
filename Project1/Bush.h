#pragma once
#include "GameObject.h"

#define ANIID_TYPE_1 20261
#define ANIID_TYPE_2 20271
#define ANIID_TYPE_3 20281
#define BUSH_SCALEX 0.7
#define BUSH_SCALEY 0.7

class CBush : public CGameObject
{
protected:
	int type;
public:
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CBush(float x, float y,int type);
};

