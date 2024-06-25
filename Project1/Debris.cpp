#include "Debris.h"
#include "playScene.h"

CBrickDebris::CBrickDebris(float x, float y)
{
	for (int i = 1; i <= 4; i++)
		debris.push_back(new CDebris(x, y, i));
	CPlayScene* scene=(CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(this,1);
	time_out = DEBRIS_TIME_OUT;
}

void CBrickDebris::Render() {
	for (int i = 0; i < debris.size(); i++)
		debris[i]->Render();
}

void CBrickDebris::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	time_out -= dt;
	if (time_out <= 0)
	{
		for (CDebris* ptr : debris)
			delete ptr;
		debris.clear();
		Delete();
	}

	for (int i = 0; i < debris.size(); i++)
		debris[i]->Update(dt, coObjects);
}

void CDebris::Render() {
	if (type == 1 || type ==3)
		CSprites::GetInstance()->Get(SPRITE_ID_DEBRIS_1)->Draw(x, y,0.3,0.3);
	else
		CSprites::GetInstance()->Get(SPRITE_ID_DEBRIS_2)->Draw(x, y,0.3,0.3);
}

void CDebris::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	y += vy * dt;
	x += vx * dt;
}

