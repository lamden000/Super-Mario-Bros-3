#include "Mushroom.h"
#include "PlayScene.h"

CMushroom::CMushroom(float x, float y,int type) :CGameObject(x, y)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	if(x<mario_x)
		this->vx = -MUSHROOM_WALKING_SPEED;
	else 
		this->vx = MUSHROOM_WALKING_SPEED;

	this->ay = MUSHROOM_GRAVITY;
	this->vy = -MUSHROOM_ESCAPE_BLOCK_SPEED;
	this->type = type;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::EscapeBlock() {
	vy = -MUSHROOM_ESCAPE_BLOCK_SPEED;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	int aniId = -1;
	if(type==MUSHROOM_TYPE_RED)
		aniId = ID_ANI_RED_MUSHROOM;
	else
		aniId = ID_ANI_GREEN_MUSHROOM;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

