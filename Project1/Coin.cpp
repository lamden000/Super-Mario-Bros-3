#include "Coin.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFromBlock)
	{
		vy += COIN_GRAVITY * dt;
		timeOut += dt;
		if(timeOut > FROM_BLOCK_TIMEOUT )
			this->Delete();
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(isFromBlock)
		animations->Get(ID_ANI_COIN_FROM_BLOCK)->Render(x, y);
	else
		animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if ( e->obj->IsBlocking())
	{
		vy = -COIN_ESCAPE_BLOCK_SPEED_Y;
	}
}

void CCoin::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CCoin::EscapeBlock() {
	vy = -COIN_ESCAPE_BLOCK_SPEED_Y;
	isFromBlock = true;
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}
