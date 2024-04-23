#pragma once
#include "GameObject.h"

#define ANIID 347
#define LOGO_SCALEX 0.2f
#define LOGO_SCALEY 0.2f
#define LOGO_SPEEDY 0.4f

class CLogo : public CGameObject
{
protected:
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CLogo(float x, float y);
};

