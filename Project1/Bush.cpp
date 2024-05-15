#include "Bush.h"
CBush::CBush(float x, float y,int type, int direction)
{
	this->direction = direction;
	this->x = x;
	this->y = y;
	this->type = type;
}


void CBush::Render()
{
	int AniID=-1;
	if (type == 1)
		AniID = BUSH_ANIID_TYPE_1_LEFT;
	else if(type==2)
		AniID= BUSH_ANIID_TYPE_2_LEFT;
	else if(type==3)
		AniID = BUSH_ANIID_TYPE_3_LEFT;
	if (direction == BUSH_DIRECTION_RIGHT)
		AniID += 30;
	CAnimations::GetInstance()->Get(AniID)->Render(x, y, BUSH_SCALEX, BUSH_SCALEY);
}

