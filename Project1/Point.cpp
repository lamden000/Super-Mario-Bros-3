#include"Point.h"
#include"PlayScene.h"

CPoint::CPoint(float x, float y, int value) :CGameObject(x, y)
{
	vy = -POINT_SPEED_Y;
	timeOut = 0;
	this->value = value;
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(this,5);
};

void CPoint::Render()
{
	int aniId = -1;
	if (value == 100)
		aniId = ID_ANI_POINT_100;
	else if(value==200)
		aniId = ID_ANI_POINT_200;
	else if (value == 1000)
		aniId = ID_ANI_POINT_1000;
	else 
		aniId = ID_ANI_POINT_LEVEL_UP;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, POINT_SCALEX, POINT_SCALEY);
}
void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	timeOut += dt;
	if (timeOut >=POINT_TIMEOUT)
	{
		this->Delete();
	}
}