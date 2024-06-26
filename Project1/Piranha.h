#pragma once
#include"Venus.h"

#define ID_ANI_PIRANHA_GREEN 21003
#define PIRANHA_TYPE_GREEN 1
#define PIRANHA_TYPE_RED 2

class CPiranha : public CVenus {
public:
	CPiranha(float x,float y,int type):CVenus(x,y,type){}
	void Grow(DWORD dt, float mario_x, float mario_y);
	virtual void Render();
};