
#include "PlayScene.h"
#include"KeyEventHandlerForMario.h"

CPortal::CPortal(float l, float t, float r, float b, float tele_x, float tele_y)
{
	this->tele_x = tele_x;
	this->tele_y = tele_y;
	isActive = false;
	x = l;
	y = t;
	width = r - l;
	height = b - t;
}

void CPortal::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive)
	{
		//check if mario is in side the bounding box
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		float ml, mt,mb,mr;
		int mState;
		CMario* mario = (CMario*)scene->GetPlayer();
		mState = mario->GetState();
		mario->GetBoundingBox(ml, mt,mr,mb);
		float l, t, b, r;
		GetBoundingBox(l, t, r, b);

		if (mState == MARIO_STATE_TRAVELLING_UP || mState == MARIO_STATE_TRAVELLING_DOWN)
		{
			static int travelTime = 0;
			static bool teleported = false;
			travelTime += dt;

			if ((travelTime >= PORTAL_MAX_TRAVEL_TIME / 2 && travelTime <= PORTAL_MAX_TRAVEL_TIME)&&!teleported)
			{
				if (mState == MARIO_STATE_TRAVELLING_UP)
					mario->SetIsUnderGround(false);
				else
					mario->SetIsUnderGround(true);

				teleported = true;
				mario->SetPosition(tele_x, tele_y);
			}
			else if (travelTime > PORTAL_MAX_TRAVEL_TIME)
			{
				mario->SetState(MARIO_STATE_RELEASE_JUMP);
				travelTime = 0;
				teleported = false;
				CGame::GetInstance()->SetKeyHandler(scene->GetKeyEventHandler());
			}
		}
		else if (mr < l || ml >  r || mb< t || mt > b) {
				isActive = false;
				mario->SetPortal(NULL);
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x-width/2 ;
	t = y-height/2 ;
	r = x + width/2;
	b = y + height/2;
}