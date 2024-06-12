#pragma once
#include "GameObject.h"

#define FIREBALL_TIMEOUT 10000

#define FIREBALL_SPEED 0.06f

#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8
#define ANI_ID_FIREBALL 94

#define FIREBALL_SCALEX 0.3f
#define  FIREBALL_SCALEY 0.3

#define FIREBALL_MID_TRAJECTORY_RANGE_X 80
#define FIREBALL_MID_TRAJECTORY_RANGE_Y 30

#define  FIREBALL_HIGH_TRAJECTORY_T 0.6
#define  FIREBALL_MID_HIGH_TRAJECTORY_T 0.3
#define  FIREBALL_MID_LOW_TRAJECTORY_T -0.4
#define  FIREBALL_LOW_TRAJECTORY_T -1

class CFireBall : public CGameObject
{
protected:
	float t;
	float x_start;
	float y_start;
	DWORD timeOut;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CFireBall(float x, float y);
};
