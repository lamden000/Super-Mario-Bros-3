#pragma once

#include "GameObject.h"

#define ID_ANI_GREEN_VENUS_LOOK_UP_LEFT 74
#define ID_ANI_GREEN_VENUS_LOOK_UP_RIGHT 75
#define ID_ANI_GREEN_VENUS_LOOK_DOWN_LEFT 76
#define ID_ANI_GREEN_VENUS_LOOK_DOWN_RIGHT 77

#define ID_ANI_RED_VENUS_LOOK_UP_LEFT 64
#define ID_ANI_RED_VENUS_LOOK_UP_RIGHT 65
#define ID_ANI_RED_VENUS_LOOK_DOWN_LEFT 66
#define ID_ANI_RED_VENUS_LOOK_DOWN_RIGHT 67

#define VENUS_BBOX_WIDTH 16
#define GREEN_VENUS_BBOX_HEIGHT 23
#define RED_VENUS_BBOX_HEIGHT 32

#define VENUS_TYPE_GREEN 1
#define VENUS_TYPE_RED 2

#define VENUS_LOW_RANGE_X	50
#define VENUS_LOW_RANGE_Y	50
#define VENUS_GROW_SPEED	0.025f   
#define VENUS_SHOOTING_TIME	1500

#define GREEN_VENUS_GROWN_HEIGHT 18
#define RED_VENUS_GROWN_HEIGHT 23
#define VENUS_SCALEX 0.35f
#define VENUS_SCALEY 0.35f

class CVenus : public CGameObject {
protected:
	int type;
	float y_start;
	bool isGoingUp;
public:
	CVenus(float x, float y,int type) : CGameObject(x, y) {
		this->type = type;
		this->y_start = y;
		this->vy = VENUS_GROW_SPEED;
		isGoingUp = false;
	}
	void Render();
	void Grow(DWORD dt, float mario_x, float mario_y);
	void Shoot(DWORD dt);
	int IsBlocking() { return 0; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};