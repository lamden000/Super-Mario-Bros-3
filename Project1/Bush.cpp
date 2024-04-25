#include "Bush.h"
CBush::CBush(float x, float y,int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
}


void CBush::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}


void CBush::Render()
{
	if(type==1)
		CAnimations::GetInstance()->Get(ANIID_TYPE_1)->Render(x, y,BUSH_SCALEX, BUSH_SCALEY);
	else if(type==2)
		CAnimations::GetInstance()->Get(ANIID_TYPE_2)->Render(x, y, BUSH_SCALEX, BUSH_SCALEY);
	else if (type == 3)
		CAnimations::GetInstance()->Get(ANIID_TYPE_3)->Render(x, y, BUSH_SCALEX, BUSH_SCALEY);
}

