#include "OverWorldUI.h"
#include "PlayScene.h"

void COverWorldUI::Render()
{
	float cx, cy, xx, screenHeight;
	int point, coin, life, runTimeSection;
	DWORD timeLimit;
	float numberWidth = 10;
	vector<int> digits;
	CGame* game = CGame::GetInstance();
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CSprites* sprites = CSprites::GetInstance();

	game->GetCamPos(cx, cy);
	coin = game->GetCoin();
	point = game->GetPoint();
	life = game->GetLife();
	timeLimit = scene->GetTimeLimit();

	//Render main board
	sprites->Get(ID_SPRITE_MAIN_BOARD)->Draw(x, y, 0.4, 0.4);

	//Render world number
	sprites->Get(ID_SPRITE_NUMBER_BASE + 1)->Draw(x - 43, y - 4, 0.4, 0.4);

	//Render point
	xx = x + 35;
	digits = getDigits(point);
	for (int i = 0; i < 7; i++)
	{
		if (i >= digits.size())
			sprites->Get(ID_SPRITE_NUMBER_BASE)->Draw(xx, y + 6, 0.4, 0.4);
		else
			sprites->Get(ID_SPRITE_NUMBER_BASE + digits[i])->Draw(xx, y + 6, 0.4, 0.4);
		xx -= numberWidth;
	}

	//Render coin
	xx = x + 73;
	digits = getDigits(coin);
	for (int i = 0; i < digits.size(); i++)
	{
		sprites->Get(ID_SPRITE_NUMBER_BASE + digits[i])->Draw(xx, y - 5, 0.4, 0.4);
		xx += numberWidth;
	}

	//Render life
	xx = x - 50;
	digits = getDigits(life);
	for (int i = 0; i < digits.size(); i++)
	{
		sprites->Get(ID_SPRITE_NUMBER_BASE + digits[i])->Draw(xx, y + 6, 0.4, 0.4);
		xx += numberWidth;
	}

	//Render time limit
	xx = x + 65;
	digits = getDigits(timeLimit);
	for (int i = digits.size() - 1; i >= 3; i--)
	{
		sprites->Get(ID_SPRITE_NUMBER_BASE + digits[i])->Draw(xx, y + 6, 0.4, 0.4);
		xx += numberWidth;
	}

	xx = x - 30;
	int arrowWidth = 11;
	for (int i = 0; i < 7; i++)
	{
		if (i < 6)
		{
			sprites->Get(ID_SPRITE_BLACK_ARROW)->Draw(xx, y - 4, 0.4, 0.4);
		}
		else
		{
			sprites->Get(ID_SPRITE_BLACK_P)->Draw(xx + 2, y - 4, 0.4, 0.4);
		}
		xx += arrowWidth;
	}
}