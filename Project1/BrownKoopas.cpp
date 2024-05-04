#include "BrownKoopas.h"

CBrownKoopas::CBrownKoopas(float x, float y,int level) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = BROWNKOOPAS_GRAVITY;
	die_start = -1;
	SetState(BROWNKOOPAS_STATE_WALKING);
}

void CBrownKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BROWNKOOPAS_STATE_SHELL)
	{
		left = x - BROWNKOOPAS_BBOX_WIDTH / 2;
		top = y - BROWNKOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + BROWNKOOPAS_BBOX_WIDTH;
		bottom = top + BROWNKOOPAS_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BROWNKOOPAS_BBOX_WIDTH / 2;
		top = y - BROWNKOOPAS_BBOX_HEIGHT / 2;
		right = left + BROWNKOOPAS_BBOX_WIDTH;
		bottom = top + BROWNKOOPAS_BBOX_HEIGHT;
	}
}

void CBrownKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBrownKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBrownKoopas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CBrownKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == BROWNKOOPAS_STATE_SHELL) && (GetTickCount64() - die_start > BROWNKOOPAS_REVIVE_TIME))
	{
		SetState(BROWNKOOPAS_STATE_WALKING);
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBrownKoopas::Render()
{
	int aniId=-1;
	if (vx > 0)
	{
		if (level = BROWNKOOPAS_LEVEL_BIG)
		{

		}
		else{}
	}
	if (state == BROWNKOOPAS_STATE_SHELL)
	{
		if(level==BROWNKOOPAS_LEVEL_SMALL)
			aniId = ID_ANI_SMALL_BROWNKOOPAS_SHELL;
		else 
			aniId = ID_ANI_BIG_BROWNKOOPAS_SHELL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBrownKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BROWNKOOPAS_STATE_SHELL:
		die_start = GetTickCount64();
		y += (BROWNKOOPAS_BBOX_HEIGHT - BROWNKOOPAS_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BROWNKOOPAS_STATE_WALKING:
		vx = -BROWNKOOPAS_WALKING_SPEED;
		break;
	}
}
