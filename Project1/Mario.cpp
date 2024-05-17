#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Coin.h"
#include "Portal.h"
#include "Luigi.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "SpawnPoint.h"
#include "PlayScene.h"
#include "QuestionBlock.h"
#include "Venus.h"
#include "FireBall.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CMario::OnNoCollision(DWORD dt)
{
	isOnPlatform = false;
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) 
			isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
			vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrownKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CLuigi*>(e->obj))
		OnCollisionWithLuigi(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CSpawnPoint*>(e->obj))
		OnCollisionWithSpawnPoint(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQestionBlock(e);
	else if (dynamic_cast<CVenus*>(e->obj)|| dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithVenus(e);

}
#pragma region collision_with
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->DecreaseLevel();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CBrownKoopas* koopas = dynamic_cast<CBrownKoopas*>(e->obj);

	if ((e->ny < 0) && koopas->GetState() ==BROWNKOOPAS_STATE_WALKING )
	{
		koopas->DecreaseLevel();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_SHELL&& koopas->GetState() != BROWNKOOPAS_STATE_REVIVING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			else {
				koopas->SetState(BROWNKOOPAS_STATE_SHELL_BOUNCING,nx);
			}
		}
	}
	float x, y;
	koopas->GetPosition(x, y);
	koopas->SetPosition(x, y - 2.0f);
}

void CMario::OnCollisionWithLuigi(LPCOLLISIONEVENT e)
{
	if (e->ny>0)
	{
		CLuigi* luigi = dynamic_cast<CLuigi*>(e->obj);
		if (luigi->GetState() != LUIGI_STATE_DIE)
		{			
			this->SetState(MARIO_STATE_SIT);
			luigi->JumpDeflect();
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	if(level<MARIO_LEVEL_FOX)
		SetLevel(MARIO_LEVEL_FOX);
	e->obj->Delete();
}

void CMario::OnCollisionWithSpawnPoint(LPCOLLISIONEVENT e)
{
	CSpawnPoint* p = (CSpawnPoint*)e->obj;
	CPlayScene* currenScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	currenScene->_ParseSection_OBJECTS(p->GetSpawnObjectDetai());
	e->obj->Delete();
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = (CMushroom*)e->obj;
	if (level == MARIO_LEVEL_SMALL&&mushroom->GetType()==MUSHROOM_TYPE_RED)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithQestionBlock(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		CQuestionBlock* block = (CQuestionBlock*)e->obj;
		block->Reward();	
	}
}
#pragma endregion
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFox()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId =ID_ANI_MARIO_FOX_JUMP_RUN_RIGHT;
			else
				aniId =ID_ANI_MARIO_FOX_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId =ID_ANI_MARIO_FOX_JUMP_WALK_RIGHT;
			else
				aniId =ID_ANI_MARIO_FOX_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId =ID_ANI_MARIO_FOX_SIT_RIGHT;
			else
				aniId =ID_ANI_MARIO_FOX_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId =ID_ANI_MARIO_FOX_IDLE_RIGHT;
				else aniId =ID_ANI_MARIO_FOX_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId =ID_ANI_MARIO_FOX_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId =ID_ANI_MARIO_FOX_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId =ID_ANI_MARIO_FOX_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId =ID_ANI_MARIO_FOX_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId =ID_ANI_MARIO_FOX_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId =ID_ANI_MARIO_FOX_WALKING_LEFT;
			}

	if (aniId == -1) aniId =ID_ANI_MARIO_FOX_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
	{
		if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_DIE;
		else
			aniId = ID_ANI_FOX_MARIO_DIE;
	}
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_FOX)
		aniId = GetAniIdFox();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if ((isOnPlatform && level != MARIO_LEVEL_SMALL))
		{
			state = MARIO_STATE_IDLE;
			vx = 0; vy = 0.0f; ax = 0;
			y += MARIO_SIT_HEIGHT_ADJUST;
			isSitting = true;
		}
		break;
	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG||level==MARIO_LEVEL_FOX)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

