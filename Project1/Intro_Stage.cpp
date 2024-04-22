#include "Intro_Stage.h"
#include"debug.h"
#include"Mario.h"
CStage::CStage(float x, float y)
{
	this->x = x;
	this->y = y;
}


void CStage::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);	
}

void CStage::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y, STAGE_SCALEX, STAGE_SCALEY);
}

void CStage::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = STAGE_BBOX_LEFT;
	t = STAGE_BBOX_TOP;
	r = l + STAGE_BBOX_OFFSET;
	b = t + STAGE_BBOX_OFFSET;
}