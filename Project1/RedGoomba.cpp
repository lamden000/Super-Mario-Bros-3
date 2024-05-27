#include <cstdlib>

#include "RedGoomba.h"
#include "debug.h"
#include "Playscene.h"

CRedGoomba::CRedGoomba(float x, float y, int level) :CGoomba(x, y,level)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CRedGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CRedGoomba::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	x += vx * dt;
	isOnPlatform = false;
};

void CRedGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny < 0)
	{
		vy = 0;
		if (state != GOOMBA_STATE_JUMP_READY)
			state = GOOMBA_STATE_WALKING;
		isOnPlatform = true;
	}
	else if (e->ny > 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CRedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (level == GOOMBA_LEVEL_WINGS)
	{
		Hop();
		ChasePlayer();
	}
	else ax = 0;
	vy += ay * dt;
	vx += ax * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRedGoomba::Hop()
{
	if (GetTickCount64() - GOOMBA_JUMP_COOLDOWN >= jump_start)
	{
		if (isOnPlatform)
			SetState(GOOMBA_STATE_JUMP_READY);
		if (GetTickCount64() - GOOMBA_JUMP_COOLDOWN - GOOMBA_JUMP_READY_TIME >= jump_start)
		{
			SetState(GOOMBA_STATE_JUMP);
		}
	}
}

void CRedGoomba::ChasePlayer()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	if (x < mario_x)
	{
		if (vx <= GOOMBA_WALKING_SPEED)
			ax = GOOMBA_ACEL_X;
		else ax = 0;
	}
	else
	{
		if (vx >= -GOOMBA_WALKING_SPEED)
			ax = -GOOMBA_ACEL_X;
		else ax = 0;
	}
}

void CRedGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	if (level == GOOMBA_LEVEL_WINGS)
	{
		aniId = ID_ANI_GOOMBA_WALKING_WITH_WINGS;
		if (state == GOOMBA_STATE_JUMP_READY)
		{
			aniId = ID_ANI_GOOMBA_JUMP_READY;
		}
		else if (state == GOOMBA_STATE_JUMP_READY)
		{
			aniId = ID_ANI_GOOMBA_JUMP_READY;
		}
		else if (state == GOOMBA_STATE_JUMP)
		{
			aniId = ID_ANI_GOOMBA_JUMP;
		}
	}

	//RenderBoundingBox();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y, GOOMBA_SCALEX, GOOMBA_SCALEY);
}


void CRedGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_JUMP:
		jump_start = GetTickCount64();
		vy = -GOOMBA_JUMP_SPEED;
		break;
	case GOOMBA_STATE_JUMP_READY:
		vy = -GOOMBA_JUMP_READY_SPEED;
		break;
	}
}
