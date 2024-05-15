#pragma once
#include "GameObject.h"

#define ANIID 347
#define ANIID_NUMBER_3 348
#define LOGO_SHAKE_SPEED 0.8f
#define LOGO_SPEEDY 0.4f
#define LOGO_ALTITUDE 45
#define LOGO_SCALEX 0.9f
#define LOGO_SCALEY 0.9f
#define LOGO_SHAKE_TIME 1000

class CLogo : public CGameObject
{
protected:
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CLogo(float x, float y);
};

