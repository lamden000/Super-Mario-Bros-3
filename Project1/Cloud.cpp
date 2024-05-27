#include"Cloud.h"

CCloud::CCloud(float x, float y)
{
	this->x = x;
	this->y = y;
}


void CCloud::Render()
{
	CAnimations::GetInstance()->Get(CLOUD_ANIID)->Render(x, y,CLOUD_SCALEX,CLOUD_SCALEY);
}

