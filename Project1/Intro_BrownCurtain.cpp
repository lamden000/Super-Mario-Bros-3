#include "Intro_BrownCurtain.h"
CBrownCurtain::CBrownCurtain(float x,float y) 
{
	this->x = x;
	this->y = y;
	this->vy = CURTAIN_SPEEDY;
}


void CBrownCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y < CURTAIN_ALTITUDE) return;
	y -= vy * dt;
	CGameObject::Update(dt, coObjects);
}


void CBrownCurtain::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y,CURTAIN_SCALEX, CURTAIN_SCALEY);
}

