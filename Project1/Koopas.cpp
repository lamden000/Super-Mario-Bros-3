#include "Koopas.h"
#include "debug.h"

CBrownKoopas::CBrownKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	SetState(BROWNKOOPAS_STATE_WALKING);
}

void CBrownKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BROWNKOOPAS_STATE_SHELL|| state == BROWNKOOPAS_STATE_REVIVING|| state == BROWNKOOPAS_STATE_SHELL_BOUNCING)
	{
		left = x - BROWNKOOPAS_BBOX_WIDTH / 2;
		top = y - BROWNKOOPAS_BBOX_HEIGHT_SHELL/ 2;
		right = left + BROWNKOOPAS_BBOX_WIDTH;
		bottom = top + BROWNKOOPAS_BBOX_HEIGHT_SHELL;
	}
	else {
		left = x - BROWNKOOPAS_BBOX_WIDTH / 2;
		top = y - BROWNKOOPAS_BBOX_HEIGHT / 2;
		right = left + BROWNKOOPAS_BBOX_WIDTH;
		bottom = top + BROWNKOOPAS_BBOX_HEIGHT;
	}
}

void CBrownKoopas::OnNoCollision(DWORD dt)
{
	if (state == BROWNKOOPAS_STATE_WALKING&&!steppedBack)
	{
		vx = -vx;
		steppedBack = true;
		if ( state == BROWNKOOPAS_STATE_SHELL)
			y += vy * dt;
	}
	else {
		x += vx * dt;
		y += vy * dt;
	}

};

void CBrownKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBrownKoopas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		steppedBack = false;
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
	if ((state == BROWNKOOPAS_STATE_SHELL|| state == BROWNKOOPAS_STATE_REVIVING) && (GetTickCount64() - die_start > BROWNKOOPAS_SHELL_TIME))
	{
		SetState(BROWNKOOPAS_STATE_REVIVING);
		if ((GetTickCount64() - die_start > BROWNKOOPAS_SHELL_TIME+BROWNKOOPAS_REVIVE_TIME))
		{
			SetState(BROWNKOOPAS_STATE_WALKING);
			y -= (BROWNKOOPAS_BBOX_HEIGHT - BROWNKOOPAS_BBOX_HEIGHT_SHELL) / 2;
			die_start = 0;
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBrownKoopas::Render()
{
	int aniId = -1;
	if (vx >= 0)
	{
		aniId = ID_ANI_BROWNKOOPAS_WALKING_RIGHT;
	}
	else if (vx <0) {
		aniId = ID_ANI_BROWNKOOPAS_WALKING_LEFT;
	}
	if (state == BROWNKOOPAS_STATE_SHELL)
	{
		aniId = ID_ANI_BROWNKOOPAS_SHELL;
	}
	else if(state == BROWNKOOPAS_STATE_REVIVING)
	{
		aniId = ID_ANI_BROWNKOOPAS_REVIVING;
	}
	else if (state == BROWNKOOPAS_STATE_SHELL_BOUNCING)
	{
		aniId = ID_ANI_BROWNKOOPAS_SHELL_BOUNCING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y,BROWKOOPAS_SCALEX,BROWKOOPAS_SCALEY);
	//RenderBoundingBox();
}

void CBrownKoopas::SetState(int state,float nx)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BROWNKOOPAS_STATE_SHELL:
		die_start = GetTickCount64();
		y -= (BROWNKOOPAS_BBOX_HEIGHT - BROWNKOOPAS_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		break;
	case BROWNKOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case BROWNKOOPAS_STATE_SHELL_BOUNCING:
		if (nx > 0)
		{
			vx = KOOPAS_BOUNCING_SPEED;
		}
		else 
			vx = -KOOPAS_BOUNCING_SPEED;
		break;
	}
}
