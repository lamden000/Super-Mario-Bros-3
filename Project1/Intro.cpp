#include "Intro.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "MenuKeyEventHandler.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "IntroGoomba.h"
#include "Platform.h"
#include "Intro_BrownCurtain.h"
#include "Intro_Stage.h"
#include "Luigi.h"
#include "Logo.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "Bush.h"
#include "Point.h"
#include "IntroKoopas.h"
#include "MenuUI.h"

#include "KeyEventHandlerForMario.h"
#include "KeyHandlerForLuigi.h"

CIntro::CIntro(int id, LPCWSTR filePath) :
	CPlayScene(id, filePath)
{
	player = NULL;
	action = 0;
	key_handler = new CMenuKeyEventHandler(this);
	introTimer = 0;
}

void CIntro::Render()
{

	CGame* g = CGame::GetInstance();
	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if ((introTimer >= 7000&& introTimer<7600)|| introTimer>7800)
	{
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR_2);
	}
	else if (introTimer >= 7600 &&introTimer<=7800)
	{
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR_3);
	}
	else {
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR_1);
	}

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	objects[STAGE_ID]->Render();
	if(introTimer>=21500)
		player->Render();
	for (int i = 1; i < objects.size(); i++)
	{
		if (i==CURTAIN_ID||i==STAGE_ID||i==LUIGI_ID) continue;
			objects[i]->Render();
	}
	if (introTimer>1700&&introTimer<21500)
	{
		player->Render();
		objects[LUIGI_ID]->Render();
	}
	objects[CURTAIN_ID]->Render();
	pSwapChain->Present(0, 0);
}

void CIntro::Update(DWORD dt)
{
	if (player == NULL) return;

	introTimer += dt;
	if (introTimer <1000) return;

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	objects[CURTAIN_ID]->Update(dt, &coObjects);
	if (introTimer<2000) return;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (i == CURTAIN_ID)
			continue;
		objects[i]->Update(dt, &coObjects);
	}

	if (this->action == 1)
	{
		float a, b, x, y;
		player->GetPosition(a, b);
		objects[LUIGI_ID]->GetPosition(x, y);
		if (a - x <= 120)
			AutoRun(2);
	}
	else if (this->action == 2) {
		if (introTimer>5000)
			AutoRun(3);
	}
	else if (this->action == 3)
	{
		if (introTimer>5500)
			AutoRun(4);
	}
	else if (this->action == 4)
	{
		float a, b, x, y;
		player->GetPosition(a, b);
		objects[LEAF_ID]->GetPosition(x, y);
		if (b - y <= 80)
			AutoRun(5);
	}
	else if (this->action == 5)
	{
		float vx, vy,mx,my;
		player->GetSpeed(vx, vy);
		if (vy>0.25 )
			player->SetState(MARIO_STATE_JUMP);
		if(vy==0)
			player->SetState(MARIO_STATE_WALKING_RIGHT);
		if (introTimer > 10800)
		{
			player->SetState(MARIO_STATE_IDLE);
			AutoRun(6);
		}	
	}
	else if (this->action == 6)
	{
		if (introTimer > 12000)
			AutoRun(7);
	}
	else if (this->action == 7)
	{
		if (introTimer > 12800)
			AutoRun(8);
	}
	else if (this->action == 8)
	{
		float mx, my, kx, ky;
		objects[objects.size() - 1]->GetPosition(kx, ky);
		player->GetPosition(mx, my);	
		if (kx - mx <= 40 && kx > mx)
			player->SetState(MARIO_STATE_JUMP);
		if (kx > mx && kx < mx + MARIO_BIG_BBOX_WIDTH +5)
			AutoRun(9);
	}
	else if (this->action == 9)
	{
		if (introTimer > 14000 && introTimer < 15000)
		{
			CMario* mario = (CMario*)player;
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
			mario->Hold();
		}
		else if (introTimer >= 15300)
		{
			AutoRun(10);
			objects[LUIGI_ID]->SetState(LUIGI_STATE_WALKING_RIGHT);
		}
	}
	else if (this->action == 10)
	{
		if (introTimer > 17000)
			AutoRun(11);
	}
	else if (this->action == 11)
	{
		float mx, my, kx, ky;
		objects[objects.size() - 1]->GetPosition(kx, ky);
		player->GetPosition(mx, my);
		if (mx - kx <= 20 && kx < mx)
			AutoRun(12);
	}
	else if (this->action == 12)
	{
		if (introTimer > 19000 && introTimer < 20500)
			player->SetState(MARIO_STATE_WALKING_RIGHT);
		else if (introTimer >= 20500 && introTimer < 21200)
			player->SetState(MARIO_STATE_WALKING_LEFT);
		else if (introTimer >= 21200)
			AutoRun(13);
	}
	else if (this->action == 13)
	{
		if (introTimer >= 21800)
			AutoRun(14);
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	PurgeDeletedObjects();
}

void CIntro::AutoRun(int action)
{
	if (action == 1)
	{
		objects[LUIGI_ID]->SetState(LUIGI_STATE_WALKING_RIGHT);
		player->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (action == 2)
	{
		objects[LUIGI_ID]->SetState(LUIGI_STATE_JUMP);
	}
	else if (action == 3)
	{
		player->SetState(MARIO_STATE_SIT_RELEASE);
	}
	else if (action == 4)
	{
		CBush* bush1 = new CBush(15, 158, 4, 2026, 2026, 2027);
		CBush* bush2 = new CBush(30, 158, 2, 2026, 2026, 2027);
		CBush* bush3 = new CBush(286, 158, 5, 2026, 2026, 2027);
		CBush* bush4 = new CBush(269, 158, 3, 2026, 2026, 2027);
		CBush* bush5 = new CBush(252, 158, 1, 2027, 2026, 2026);
		objects.push_back(bush1);
		objects.push_back(bush2);
		objects.push_back(bush3);
		objects.push_back(bush4);
		objects.push_back(bush5);
		CIntroGoomba* goomba = new CIntroGoomba(100, -150, 1);
		CGreenKoopas* koopas1 = new CGreenKoopas(150, 0, 1);
		CMushroom* greenMushroom = new CMushroom(250, -50, 2);
		CMushroom* redMushroom = new CMushroom(50, -50, 1);
		koopas1->SetState(KOOPAS_STATE_SHELL);
		objects.push_back(goomba);
		objects.push_back(redMushroom);
		objects.push_back(greenMushroom);
		objects.push_back(koopas1);
	}
	else if (action == 5)
	{
		player->SetState(MARIO_STATE_JUMP);
		player->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (action == 6)
	{
		CLuigi* luigi = (CLuigi*)objects[LUIGI_ID];
		CGreenKoopas* koopas= (CGreenKoopas*)objects[objects.size() - 1];
		luigi->SetPosition(400, 100);
		luigi->SetHoldedObject(koopas);
		koopas->SetIsHolded(true);
		koopas->SetState(KOOPAS_STATE_SHELL);
		luigi->SetState(LUIGI_STATE_WALKING_LEFT);
		objects[objects.size() - 2]->Delete();
		objects[objects.size() - 3]->Delete();

	}
	else if (action == 7)
	{
		objects[LUIGI_ID]->SetState(LUIGI_STATE_IDLE);
		player->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (action == 8)
	{
		CLuigi* luigi = (CLuigi*)objects[LUIGI_ID];
		luigi->ReleaseHold();
	}
	else if (action == 9)
	{
		player->SetState(MARIO_STATE_RELEASE_JUMP);
	}
	else if (action == 10)
	{
		CMario* mario = (CMario*)player;
		mario->SetState(MARIO_STATE_IDLE);
		mario->ReleaseHold();
	}
	else if (action == 11)
	{
		objects[objects.size() - 1]->SetPosition(-40,130);
	}
	else if (action == 12)
	{
		CMario* mario = (CMario*)player;
		mario->SetLevel(MARIO_LEVEL_BIG);
	}
	else if (action == 13)
	{
		player->SetState(MARIO_STATE_WALKING_RIGHT);
		objects[objects.size() - 1]->Delete();
	}
	else if (action == 14)
	{
		CMenuUI* ui = new CMenuUI(155, 140);
		CIntroKoopas* koopas1 = new CIntroKoopas(-30, 120,1);
		CIntroKoopas* koopas2 = new CIntroKoopas(-80, 100, 1);
		CIntroKoopas* koopas3 = new CIntroKoopas(-120, 100, 1);
		CIntroKoopas* koopas4 = new CIntroKoopas(-400, 100, 1);
		koopas1->SetState(KOOPAS_STATE_WALKING);
		koopas2->SetState(KOOPAS_STATE_WALKING);
		koopas3->SetState(KOOPAS_STATE_WALKING);
		koopas4->SetState(KOOPAS_STATE_RUNNING);
		objects.push_back(koopas1);
		objects.push_back(koopas2);
		objects.push_back(koopas3);
		objects.push_back(koopas4);
		objects.push_back(ui);
		player = ui;
	}
	this->action = action;
}


void CIntro::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	DebugOut(L" object type: %d\n", object_type);
	CGameObject* obj = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		obj = new CMario(x, y,MARIO_LEVEL_BIG);
		player = (CMario*)obj;
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_LUIGI:
		obj = new CLuigi(x, y);

		CGame::GetInstance()->SetKeyHandler(key_handler);
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		int level = 1;
		if (tokens.size() > 3)
			level = (int)atof(tokens[3].c_str());
		obj = new CGoomba(x, y, level); break;
	}
	case OBJECT_TYPE_BROWNCURTAIN: obj = new CBrownCurtain(x, y); break;
	case OBJECT_TYPE_STAGE: obj = new CStage(x, y); break;
	case OBJECT_TYPE_LOGO: obj = new CLogo(x, y); break;
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_BUSH:
	{
		int height = atoi(tokens[3].c_str());
		int sprite_begin = atoi(tokens[4].c_str());
		int sprite_middle = atoi(tokens[5].c_str());
		int sprite_end = atoi(tokens[6].c_str());
		obj = new CBush(x, y, height, sprite_begin, sprite_middle, sprite_end);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	objects.push_back(obj);
}

void CIntro::AddObject(LPGAMEOBJECT object,int id)
{
	if (!dynamic_cast<CPoint*>(object))
	{
		objects.push_back(object);
	}
}

