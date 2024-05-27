﻿#include "Intro.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Intro_BrownCurtain.h"
#include "Intro_Stage.h"
#include "Luigi.h"
#include "Logo.h"
#include "Leaf.h"
#include "Bush.h"
#include "Point.h"

#include "KeyEventHandlerForMario.h"
#include "KeyHandlerForLuigi.h"

CIntro::CIntro(int id, LPCWSTR filePath) :
	CPlayScene(id, filePath)
{
	player = NULL;
	action = 0;
}

void CIntro::Render()
{
	static DWORD introStartTime = GetTickCount();

	CGame* g = CGame::GetInstance();
	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	DWORD currentTime = GetTickCount64();
	DWORD passedTime = currentTime - introStartTime;

	if ((passedTime >= 7000&& passedTime<7600)|| passedTime>7800)
	{
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR_2);
	}
	else if (passedTime >= 7600 && passedTime <=7800)
	{
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR_3);
	}
	else {
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR_1);
	}

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	objects[STAGE_ID]->Render();
	for (int i = 1; i < objects.size(); i++)
	{
		if (i==CURTAIN_ID||i==STAGE_ID) continue;
			objects[i]->Render();
	}
	objects[MARIO_ID]->Render();
	objects[CURTAIN_ID]->Render();
	pSwapChain->Present(0, 0);
}

void CIntro::Update(DWORD dt)
{
	static bool waitFinished = false;
	WaitForIntro(dt, 1000, waitFinished);
	if (!waitFinished) return;

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	objects[CURTAIN_ID]->Update(dt, &coObjects);

	waitFinished = false;
	WaitForIntro(dt, 3000, waitFinished);
	if (!waitFinished) return;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (i == CURTAIN_ID)
			continue;
		objects[i]->Update(dt, &coObjects);
	}

	if (this->action == ACTION_1)
	{
		float a, b, x, y;
		objects[MARIO_ID]->GetPosition(a, b);
		objects[LUIGI_ID]->GetPosition(x, y);
		if (a - x <= 115)
		{
			AutoRun(ACTION_2);
		}
	}
	else if (this->action == ACTION_2) {
		waitFinished = false;
		WaitForIntro(dt, 9000, waitFinished);
		if (waitFinished)
			AutoRun(ACTION_3);
	}
	else if (this->action == ACTION_3)
	{
		float a, b, x, y;
		objects[MARIO_ID]->GetPosition(a, b);
		objects[LEAF_ID]->GetPosition(x, y);
		if (b-y<=80)
			AutoRun(ACTION_4);
	}
	else if (this->action == ACTION_4)
	{
		
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	PurgeDeletedObjects();
}


void CIntro::WaitForIntro(DWORD dt, DWORD introDuration, bool& waitFinished)
{
	static DWORD introTimer = 0;

	if (!waitFinished)
	{
		introTimer += dt;

		if (introTimer >= introDuration)
		{
			waitFinished = true;
		}
	}
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
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_LUIGI:
		key_handler = new CKeyHandlerForLuigi(this);
		obj = new CLuigi(x, y);
		player = (CLuigi*)obj;

		CGame::GetInstance()->SetKeyHandler(key_handler);
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		int level = 1;
		if (tokens.size() > 3)
			level = (int)atof(tokens[3].c_str());
		obj = new CGoomba(x, y, level); break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
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

void CIntro::AutoRun(int action)
{
	if (action == ACTION_1)
	{
		CMario* mario = dynamic_cast<CMario*>(objects[MARIO_ID]);
		CLuigi* luigi = dynamic_cast<CLuigi*>(objects[LUIGI_ID]);
		mario->SetAutoRunning(true);
		luigi->SetAutoRunning(true);
		luigi->SetState(LUIGI_STATE_WALKING_RIGHT);
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (action == ACTION_2)
	{
		objects[LUIGI_ID]->SetState(LUIGI_STATE_JUMP);		
	}
	else if (action == ACTION_3)
	{
		objects[MARIO_ID]->SetState(MARIO_STATE_SIT_RELEASE);
	}
	else if (action == ACTION_4)
	{
		objects[MARIO_ID]->SetState(MARIO_STATE_JUMP);
	}
	else if (action == ACTION_5)
	{
		
	}
	this->action = action;
}
