#include "Logo.h"
CLogo::CLogo(float x, float y)
{
	this->x = x;
	this->y = y;
	this->vy = LOGO_SPEEDY;
}


void CLogo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y >= LOGO_ALTITUDE)
	{
		return;
	}
	y += vy * dt;
}

void CLogo::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y,LOGO_SCALEX,LOGO_SCALEY);
	CAnimations::GetInstance()->Get(ANIID_NUMBER_3)->Render(x, y+50, LOGO_SCALEX, LOGO_SCALEY);
}

