#include "Logo.h"
CLogo::CLogo(float x, float y)
{
	this->x = x;
	this->y = y;
	this->vy = LOGO_SPEEDY;
}


void CLogo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y >= 60)
	{
		return;
	}
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
}


void CLogo::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y, LOGO_SCALEX, LOGO_SCALEY);
}

