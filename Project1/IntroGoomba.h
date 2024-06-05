#pragma once
#include"Goomba.h"

class CIntroGoomba : public CGoomba
{
protected:
	DWORD standTime;
	bool walked;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CIntroGoomba(float x, float y, int level) :CGoomba(x, y, level)
	{
		standTime = 2500;
		vx = 0;
		walked = false;
	}
};