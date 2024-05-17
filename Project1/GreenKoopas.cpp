#include "GreenKoopas.h"
#include "debug.h"
#include "QuestionBlock.h"

void CGreenKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CGreenKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGreenKoopas*>(e->obj)) return;

	if (e->ny < 0)
	{
		vy = 0;
		if(state==GREENKOOPAS_STATE_JUMP)
			state = GREENKOOPAS_STATE_WALKING;
	}
	else if (e->ny > 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQestionBlock(e);
}

void CGreenKoopas::Hop()
{
	if (GetTickCount64() - KOOPAS_JUMP_COOLDOWN >= jump_start)
	{
		if (state==GREENKOOPAS_STATE_WALKING)
			SetState(GREENKOOPAS_STATE_JUMP);
	}
}


void CGreenKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (level == GREENKOOPAS_LEVEL_WINGS)
		Hop();
	vy += ay * dt;
	vx += ax * dt;
	if ((state == KOOPAS_STATE_SHELL || state == GREENKOOPAS_STATE_REVIVING) && (GetTickCount64() - die_start > GREENKOOPAS_SHELL_TIME))
	{
		SetState(GREENKOOPAS_STATE_REVIVING);
		if ((GetTickCount64() - die_start > GREENKOOPAS_SHELL_TIME + GREENKOOPAS_REVIVE_TIME))
		{
			SetState(GREENKOOPAS_STATE_WALKING);
			y -= (GREENKOOPAS_BBOX_HEIGHT - GREENKOOPAS_BBOX_HEIGHT_SHELL) / 2;
			die_start = 0;
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGreenKoopas::Render()
{
	int aniId = -1;
	if (vx >= 0)
	{
		if (level == GREENKOOPAS_LEVEL_NORMAL)
			aniId = ID_ANI_GREENKOOPAS_WALKING_RIGHT;
		else
			aniId = ID_ANI_GREENKOOPAS_WALKING_RIGHT_WITH_WINGS;
	}
	else if (vx < 0) {
		if (level == GREENKOOPAS_LEVEL_NORMAL)
			aniId = ID_ANI_GREENKOOPAS_WALKING_LEFT;
		else
			aniId = ID_ANI_GREENKOOPAS_WALKING_LEFT_WITH_WINGS;
	}
	if (state == KOOPAS_STATE_SHELL)
	{
		aniId = ID_ANI_GREENKOOPAS_SHELL;
	}
	else if (state == GREENKOOPAS_STATE_REVIVING)
	{
		aniId = ID_ANI_GREENKOOPAS_REVIVING;
	}
	else if (state == GREENKOOPAS_STATE_SHELL_BOUNCING)
	{
		aniId = ID_ANI_GREENKOOPAS_SHELL_BOUNCING;
	}
	else if (state == GREENKOOPAS_STATE_JUMP)
	{
		if(vx<0)
			aniId = ID_ANI_GREENKOOPAS_JUMP_LEFT;
		else aniId = ID_ANI_GREENKOOPAS_JUMP_RIGHT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y, GREENKOOPAS_SCALEX, GREENKOOPAS_SCALEY);
	//RenderBoundingBox();
}

void CGreenKoopas::SetState(int state, float nx)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		die_start = GetTickCount64();
		y -= (GREENKOOPAS_BBOX_HEIGHT - GREENKOOPAS_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		break;
	case GREENKOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case GREENKOOPAS_STATE_SHELL_BOUNCING:
		if (nx > 0)
		{
			vx = KOOPAS_BOUNCING_SPEED;
		}
		else
			vx = -KOOPAS_BOUNCING_SPEED;
		break;
	case GREENKOOPAS_STATE_JUMP:
		jump_start = GetTickCount64();
		vy = -KOOPAS_JUMP_SPEED;
	}
}