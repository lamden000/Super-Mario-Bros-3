#include "P_Switch.h"
#include "PlayScene.h"

CPSwitch::CPSwitch(float x, float y) :CGameObject(x, y) {
	enable = true;
	ay = PSWITCH_REVEAL_GRAVITY;
	isRevealed = false;
};

void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PSWITCH_BBOX_WIDTH / 2;
	t = y - PSWITCH_BBOX_HEIGHT / 2;
	r = l + PSWITCH_BBOX_WIDTH;
	b = t + PSWITCH_BBOX_HEIGHT;
}
void CPSwitch::Render()
{
	if (isRevealed)
	{
		if (enable)
			CSprites::GetInstance()->Get(ID_SPRITE_ENABLE_BUTTON)->Draw(x, y, 0.3,0.3);
		else
			CSprites::GetInstance()->Get(ID_SPRITE_UNABLE_BUTTON)->Draw(x, y, 0.3,0.3);
	}
}

void CPSwitch::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		ay = 0;
	}
}

void  CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isRevealed)
	{
		CCollision::GetInstance()->Process(this, dt, coObjects);
		vy += ay * dt;
		y += vy * dt;
	}
}

void CPSwitch::BreakBrick()
{
	if (!enable||!isRevealed)
		return;
	CPlayScene* scene =(CPlayScene *) CGame::GetInstance()->GetCurrentScene();
	for (int i = 0; i < goldBlocks.size(); i++)
	{
		if(scene->IsObjectStillThere(goldBlocks[i]))
			goldBlocks[i]->TurnIntoCoin();
	}
	enable = false;
	y += PSWITCH_BBOX_HEIGHT - PSWITCH_BBOX_UNABLE_HEIGHT;
}

void CPSwitch::Reveal()
{
	if (isRevealed)
		return;
	isRevealed = true;
	vy = -PSWITCH_REVEAL_SPEED_Y;
	for (int i = 0; i < goldBlocks.size(); i++)
	{
		if (goldBlocks[i]->GetType() == GOLD_BLOCK_TYPE_P_SWITCH)
		{
			goldBlocks[i]->Reward();
			return;
		}
	}
}
