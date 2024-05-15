#pragma once
#include "GameObject.h"

#define ANIID 345
#define CURTAIN_SCALEX 1.3f
#define CURTAIN_SCALEY 1.0f
#define CURTAIN_SPEEDY 0.2f
#define CURTAIN_ALTITUDE -80

class CBrownCurtain : public CGameObject
{
protected:
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CBrownCurtain(float x, float y);
};

