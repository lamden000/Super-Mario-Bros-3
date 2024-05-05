#include "Leaf.h"
#include"debug.h"
CLeaf::CLeaf(float x, float y)
{
	this->axis = x;
	this->x = x;
	this->y = y;
	this->ax = LEAF_ACCEL_X;
	this->ay = LEAF_GRAVITY;
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
	if (x - axis >= LEAF_FLUCTUATION_RATE)
	{
		ax = -LEAF_ACCEL_X;
		vx = 0;
	}
	else if (axis-x > LEAF_FLUCTUATION_RATE) {
		ax =LEAF_ACCEL_X ;
		vx = 0;
	}
	vx += ax * dt;
	if (vy < LEAF_DROP_VY_MAX)
		vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	x += vx * dt;
}

void CLeaf::EscapeBlock() {
	vy = -LEAF_ESCAPE_BLOCK_SPEED_Y;
}

void CLeaf::Render()
{
	CAnimations::GetInstance()->Get(ANIID)->Render(x, y);
}

