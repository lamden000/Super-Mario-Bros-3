#include <algorithm>
#include "debug.h"

#include "Luigi.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Intro_Stage.h"

#include "Collision.h"

//
// Get animation ID for small LUIGI
//
int CLuigi::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == LUIGI_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_LUIGI_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_LUIGI_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_LUIGI_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_LUIGI_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_LUIGI_SIT_RIGHT;
			else
				aniId = ID_ANI_LUIGI_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_LUIGI_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_LUIGI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_LUIGI_SMALL_BRACE_RIGHT;
				else if (ax == LUIGI_ACCEL_RUN_X)
					aniId = ID_ANI_LUIGI_SMALL_RUNNING_RIGHT;
				else if (ax == LUIGI_ACCEL_WALK_X)
					aniId = ID_ANI_LUIGI_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_LUIGI_SMALL_BRACE_LEFT;
				else if (ax == -LUIGI_ACCEL_RUN_X)
					aniId = ID_ANI_LUIGI_SMALL_RUNNING_LEFT;
				else if (ax == -LUIGI_ACCEL_WALK_X)
					aniId = ID_ANI_LUIGI_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_LUIGI_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big LUIGI
//
int CLuigi::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == LUIGI_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_LUIGI_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_LUIGI_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_LUIGI_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_LUIGI_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_LUIGI_SIT_RIGHT;
			else
				aniId = ID_ANI_LUIGI_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_LUIGI_IDLE_RIGHT;
				else aniId = ID_ANI_LUIGI_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_LUIGI_BRACE_RIGHT;
				else if (ax == LUIGI_ACCEL_RUN_X)
					aniId = ID_ANI_LUIGI_RUNNING_RIGHT;
				else if (ax == LUIGI_ACCEL_WALK_X)
					aniId = ID_ANI_LUIGI_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_LUIGI_BRACE_LEFT;
				else if (ax == -LUIGI_ACCEL_RUN_X)
					aniId = ID_ANI_LUIGI_RUNNING_LEFT;
				else if (ax == -LUIGI_ACCEL_WALK_X)
					aniId = ID_ANI_LUIGI_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_LUIGI_IDLE_RIGHT;

	return aniId;
}

void CLuigi::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == LUIGI_STATE_DIE)
	{
		aniId = ID_ANI_LUIGI_DIE;
		animations->Get(aniId)->Render(x, y);
	}		
	else if (level == LUIGI_LEVEL_BIG)
	{
		aniId = GetAniIdBig();
		animations->Get(aniId)->Render(x, y,0.9,0.9);
	}		
	else if (level == LUIGI_LEVEL_SMALL)
	{
		aniId = GetAniIdBig();
		animations->Get(aniId)->Render(x, y, 0.7, 0.7);
	}
	//RenderBoundingBox();
	DebugOutTitle(L"Coins: %d", coin);
}

void CLuigi::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == LUIGI_STATE_DIE) return;

	switch (state)
	{
	case LUIGI_STATE_RUNNING_RIGHT:
		if (isSitting)
			break;
		maxVx = LUIGI_RUNNING_SPEED;
		ax = LUIGI_ACCEL_RUN_X;
		nx = 1;
		break;
	case LUIGI_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -LUIGI_RUNNING_SPEED;
		ax = -LUIGI_ACCEL_RUN_X;
		nx = -1;
		break;
	case LUIGI_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = LUIGI_WALKING_SPEED;
		ax = LUIGI_ACCEL_WALK_X;
		nx = 1;
		break;
	case LUIGI_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -LUIGI_WALKING_SPEED;
		ax = -LUIGI_ACCEL_WALK_X;
		nx = -1;
		break;
	case LUIGI_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == LUIGI_RUNNING_SPEED)
				vy = -LUIGI_JUMP_RUN_SPEED_Y;
			else
				vy = -LUIGI_JUMP_SPEED_Y;
		}
		break;

	case LUIGI_STATE_RELEASE_JUMP:
		if (vy < 0) vy += LUIGI_JUMP_SPEED_Y / 2;
		break;

	case LUIGI_STATE_SIT:
		if (isOnPlatform&& level != LUIGI_LEVEL_SMALL)
		{
			state = LUIGI_STATE_IDLE;
			isSitting = true;
			vx = 0.0f; 
			vy = 0.0f;
			ax = 0;
			y += LUIGI_SIT_HEIGHT_ADJUST;
		}
		break;

	case LUIGI_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = LUIGI_STATE_IDLE;
			y -= LUIGI_SIT_HEIGHT_ADJUST;
		}
		break;

	case LUIGI_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case LUIGI_STATE_DIE:
		JumpDeflect();
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CLuigi::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == LUIGI_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - LUIGI_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - LUIGI_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + LUIGI_BIG_SITTING_BBOX_WIDTH;
			bottom = top + LUIGI_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - LUIGI_BIG_BBOX_WIDTH / 2;
			top = y - LUIGI_BIG_BBOX_HEIGHT / 2;
			right = left + LUIGI_BIG_BBOX_WIDTH;
			bottom = top + LUIGI_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - LUIGI_SMALL_BBOX_WIDTH / 2;
		top = y - LUIGI_SMALL_BBOX_HEIGHT / 2;
		right = left + LUIGI_SMALL_BBOX_WIDTH;
		bottom = top + LUIGI_SMALL_BBOX_HEIGHT;
	}
}

void CLuigi::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == LUIGI_LEVEL_SMALL)
	{
		y -= (LUIGI_BIG_BBOX_HEIGHT - LUIGI_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CLuigi::JumpDeflect()
{
	vy -= LUIGI_JUMP_DEFLECT_SPEED;
}

