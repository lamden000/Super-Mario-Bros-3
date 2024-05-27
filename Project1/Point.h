#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_POINT_100 1013
#define ID_ANI_POINT_200 1014
#define ID_ANI_POINT_1000 1015
#define ID_ANI_POINT_LEVEL_UP 1016

#define POINT_SPEED_Y 0.035f
#define POINT_TIMEOUT 700


#define POINT_SCALEX 0.35f
#define POINT_SCALEY 0.35f


#define POINT_LEVEL_UP_VALUE -1

class CPoint : public CGameObject {
protected:
	int value;
	DWORD timeOut;
public:
	CPoint(float x, float y, int value);
	void Render();
	void Update(DWORD dt , vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};