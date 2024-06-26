#pragma once
#include "GameObject.h"

#define DEBRIS_GRAVITY 0.0005f
#define	DEBRIS_VX	0.1f
#define DEBRIS_VY	0.1f;

#define SPRITE_ID_DEBRIS_1	22000
#define SPRITE_ID_DEBRIS_2	22001

#define DEBRIS_TIME_OUT 1000

class CDebris : public CGameObject {
protected:
	float ay;
	int type;
public:
	CDebris(float x, float y,int type):CGameObject(x,y){
		this->type = type;
		ay = DEBRIS_GRAVITY;

		if(type==1||type==4)
			vx = -DEBRIS_VX;
		else 
			vx = DEBRIS_VX;

		if (type == 3 || type == 4)
			vy = 0;
		else
			vy = -DEBRIS_VY;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render();
};

class CBrickDebris : public CGameObject {
protected:
	vector <CDebris*> debris;
	int time_out;
public:
	CBrickDebris(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render();
};