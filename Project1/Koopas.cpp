#include "Koopas.h"
#include "QuestionBlock.h"
#include "Goomba.h"
#include "Point.h"
#include "Playscene.h"

CBrownKoopas::CBrownKoopas(float x, float y, int level) :CGameObject(x, y)
{
	start_x = x;
	start_y = y;
	start_level = level;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	SetState(KOOPAS_STATE_WALKING,-1);
	isHolded = false;
	this->level = level;
}


void CBrownKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(!Respawn())
	{
		if (isHolded)
			ay = 0;

		if ((state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_REVIVING) && (GetTickCount64() - die_start > BROWNKOOPAS_SHELL_TIME))
		{
			SetState(KOOPAS_STATE_REVIVING);
			if ((GetTickCount64() - die_start > BROWNKOOPAS_SHELL_TIME + BROWNKOOPAS_REVIVE_TIME))
			{
				SetState(KOOPAS_STATE_WALKING,-1);
				y -= (BROWNKOOPAS_BBOX_HEIGHT - BROWNKOOPAS_BBOX_HEIGHT_SHELL) / 2;
				die_start = 0;
			}
		}
		vy += ay * dt;
		vx += ax * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}

}

void CBrownKoopas::DropCollision()
{
	vx = -0.15;
	vy = 0;
	DebugOut(L">>> Mario DIE >>> \n");
}

void CBrownKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL|| state == KOOPAS_STATE_REVIVING|| state == KOOPAS_STATE_SHELL_BOUNCING)
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
	if (state == KOOPAS_STATE_WALKING)
	{
		if (vx > 0)
			x -= 5;
		else
			x += 5;
		vx = -vx;
	}
	else {
		x += vx * dt;
		y += vy * dt;
	}
};

bool CBrownKoopas::Respawn()
{
	CGame* game = CGame::GetInstance();
	CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
	LPGAMEOBJECT player = scene->GetPlayer();
	int  screenWidth;
	float mx, my;
	player->GetPosition(mx, my);
	screenWidth = game->GetBackBufferWidth();
	if (abs(mx - x) > screenWidth/1.9 && abs(mx - start_x) > screenWidth / 1.9)
	{
		SetState(KOOPAS_STATE_WALKING);
		x = start_x;
		y = start_y;
		level = start_level;
		return true;
	}
	return false;
}

void CBrownKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if(!dynamic_cast<CGoomba*>(e->obj)&& !dynamic_cast<CBrownKoopas*>(e->obj))
			vx = -vx;
	}
	if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQestionBlock(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
}

void CBrownKoopas::OnCollisionWithQestionBlock(LPCOLLISIONEVENT e)
{
	if (state != KOOPAS_STATE_SHELL_BOUNCING) return;
	CQuestionBlock* block = (CQuestionBlock*)e->obj;
	block->Reward();
}
void CBrownKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (state != KOOPAS_STATE_SHELL_BOUNCING) return;
	CGoomba* goomba = (CGoomba*)e->obj;
	goomba->SetState(GOOMBA_STATE_DIE);
}


void CBrownKoopas::DecreaseLevel()
{
	level--;
	if (level == 0)
	{
		SetState(KOOPAS_STATE_SHELL);
		level = 1;
	}
	new CPoint(x, y, 100);
};


void CBrownKoopas::Render()
{
	int aniId = -1;
	if (vx >= 0)
	{
		if (level == BROWNKOOPAS_LEVEL_NORMAL)
			aniId = ID_ANI_BROWNKOOPAS_WALKING_RIGHT;
		else
			aniId = ID_ANI_BROWNKOOPAS_WALKING_RIGHT_WITH_WINGS;
	}
	else if (vx <0) {
		if (level == BROWNKOOPAS_LEVEL_NORMAL)
			aniId = ID_ANI_BROWNKOOPAS_WALKING_LEFT;
		else
			aniId = ID_ANI_BROWNKOOPAS_WALKING_LEFT_WITH_WINGS;
	}
	if (state == KOOPAS_STATE_SHELL)
	{
		aniId = ID_ANI_BROWNKOOPAS_SHELL;
	}
	else if(state == KOOPAS_STATE_REVIVING)
	{
		aniId = ID_ANI_BROWNKOOPAS_REVIVING;
	}
	else if (state == KOOPAS_STATE_SHELL_BOUNCING)
	{
		aniId = ID_ANI_BROWNKOOPAS_SHELL_BOUNCING;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y,BROWKOOPAS_SCALEX,BROWKOOPAS_SCALEY);
	//RenderBoundingBox();
}

void CBrownKoopas::SetState(int state,float nx)
{
	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		die_start = GetTickCount64();
		if(this->state!=KOOPAS_STATE_SHELL_BOUNCING)
			y += (BROWNKOOPAS_BBOX_HEIGHT - BROWNKOOPAS_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_SHELL_BOUNCING:
		if (nx > 0)
		{
			vx = KOOPAS_BOUNCING_SPEED;
		}
		else 
			vx = -KOOPAS_BOUNCING_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	}
	CGameObject::SetState(state);
}
