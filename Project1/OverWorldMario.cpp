#include "OverWorldMario.h"

void COverWorldMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void COverWorldMario::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_OVERWORLD_MARIO)->Render(x,y,0.3,0.3);
	RenderBoundingBox();
}

void COverWorldMario::SetState(int state)
{
	switch (state)
	{
	case OVERWORLD_MARIO_STATE_GO_UP:
		vy = -OVERWORLD_MARIO_SPEED;
		break;
	case OVERWORLD_MARIO_STATE_GO_DOWN:
		vy = OVERWORLD_MARIO_SPEED;
		break;

	case OVERWORLD_MARIO_STATE_GO_RIGHT:
		vx= OVERWORLD_MARIO_SPEED;
		break;

	case OVERWORLD_MARIO_STATE_GO_LEFT:
		vx = -OVERWORLD_MARIO_SPEED;
		break;
	case OVERWORLD_MARIO_STATE_STAND_STILL:
		vx = 0;
		vy = 0;
		break;
	}
	this->state = state;
}

void COverWorldMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	SetCurrentStopPoint((CStopPoint*)e->obj);
	vx = 0;
	vy = 0;
}
void COverWorldMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - OVERWORLDMARIO_BBOX_WIDTH / 2;
	top = y - OVERWORLDMARIO_BBOX_HEIGHT / 2;
	right = left + OVERWORLDMARIO_BBOX_WIDTH;
	bottom = top + OVERWORLDMARIO_BBOX_HEIGHT;
}