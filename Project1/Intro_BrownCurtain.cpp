#include "Intro_BrownCurtain.h"
#include"debug.h"
CBrownCurtain::CBrownCurtain(float x,float y) 
{
	this->x = x;
	this->y = y;
	this->vy = CURTAIN_SPEEDY;
}


void CBrownCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y -= vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBrownCurtain::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y,CURTAIN_SCALEX, CURTAIN_SCALEX);
}

