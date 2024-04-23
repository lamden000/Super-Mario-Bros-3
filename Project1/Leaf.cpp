#include "Leaf.h"
#include"debug.h"
CLeaf::CLeaf(float x, float y)
{
	this->x = x;
	this->y = y;
	this->vy = LEAF_SPEEDY;
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y);
	RenderBoundingBox();
}

