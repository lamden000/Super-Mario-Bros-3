#include"IntroGoomba.h"

void CIntroGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	standTime -= dt;
	if(!walked)
	{
		if (standTime > 0)
			vx = 0;
		else
		{
			walked = true;
			vx = -GOOMBA_WALKING_SPEED;
		}
	}

	CGoomba::Update(dt,coObjects);
}
