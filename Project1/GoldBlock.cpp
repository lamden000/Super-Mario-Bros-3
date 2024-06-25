#include"GoldBlock.h"
#include"Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Debris.h"

void CGoldBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	y += vy * dt;
	if (y > start_y)
	{
		vy = 0;
		y = start_y;
	}
	if (p_switch_time > 0 )
		p_switch_time -= dt;
	else if(generated_coin==true)
		isEmpty = true;

	CCollision::GetInstance()->Process(this,dt, coObjects);
}

void CGoldBlock::Render()
{
	if(!isEmpty)
		CAnimations::GetInstance()->Get(ID_ANI_GOLD_BRICK)->Render(x,y);
	else
		CAnimations::GetInstance()->Get(ID_ANI_GOLD_BLOCK_EMPTY)->Render(x, y);
}

void CGoldBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GOLD_BLOCK_BBOX_WIDTH / 2;
	top = y - GOLD_BLOCK_BBOX_HEIGHT / 2;
	bottom = top + GOLD_BLOCK_BBOX_HEIGHT;
	right = left + GOLD_BLOCK_BBOX_WIDTH;
}

void CGoldBlock::Reward()
{
	if (!isEmpty)
	{
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		if (type == GOLD_BLOCK_TYPE_GREEN_MUSHROOM)
		{
			CMushroom* mushroom = new CMushroom(x, y, 2);
			mushroom->EscapeBlock();
			scene->AddObject(mushroom, 1);
			isEmpty = true;
		}
		else if (type == GOLD_BLOCK_TYPE_COIN)
		{
			if (!generated_coin)
			{
				p_switch_time = P_SWITCH_TIME;
				generated_coin = true;
			}
			if (p_switch_time > 0)
			{
				CCoin* coin = new CCoin(x, y);
				coin->EscapeBlock();
				scene->AddObject(coin, 1);
				vy = -0.1;
			}
		}
		else if (type == GOLD_BLOCK_TYPE_BREAKABLE)
		{
			new CBrickDebris(x, y);
			Delete();
		}
	}
}

void CGoldBlock::TurnIntoCoin() {
	CCoin* coin = new CCoin(x,y);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(coin);
	Delete();
}