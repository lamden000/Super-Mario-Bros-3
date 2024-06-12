#include "OverWorld.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Utils.h"

#include "OverWorldKeyEventHandler.h"
#include "OverWorldMario.h"
#include "OverWorldUI.h"
#include "StopPoint.h"

COverWorld::COverWorld(int id, LPCWSTR filePath):CPlayScene(id, filePath)
{
	player = NULL;
	key_handler = new COverWorldKeyEventHandler(this);
	timeLimit = 0;
}

void COverWorld::Render()
{

	CGame* g = CGame::GetInstance();
	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->ClearRenderTargetView(pRenderTargetView, OVERWORLD_BACKGROUND_COLOR);
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);
	
	CSprites::GetInstance()->Get(ID_SPRITE_OVERWORLD_BACKGROUND)->Draw(150,90,0.25,0.22);
	for (int i = objects.size()-1; i >=0 ; i--)
	{
		objects[i]->Render();
	}
	pSwapChain->Present(0, 0);
}

void COverWorld::_ParseSection_OBJECTS(string line)
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
	case OBJECT_TYPE_SCENE_UI:	obj = new COverWorldUI(x,y); break;
	case OBJECT_TYPE_OVERWORLD_MARIO:
	{
		obj = new COverWorldMario(x, y);
		player = obj;
		break;
	}
	case OBJECT_TYPE_STOP_POINT:
	{
		vector<int> allowMoveDirection;
		int level = atoi(tokens[3].c_str());
		for (int i = 4; i < tokens.size(); i++)
			allowMoveDirection.push_back(atoi(tokens[i].c_str()));
		obj = new CStopPoint(x,y,level,allowMoveDirection);
		COverWorldMario* mario = (COverWorldMario*)player;
		if (mario->GetCurrentStopPoint() == NULL)
			mario->SetCurrentStopPoint((CStopPoint*)obj);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	objects.push_back(obj);
}

void COverWorld::Update(DWORD dt)
{
	vector<LPGAMEOBJECT>& coObjects = objects;
	if (!objects.empty()) {
		CMario* player = (CMario*)objects.front();
		for (size_t i = 0; i < objects.size(); i++) {
			objects[i]->Update(dt, &coObjects);
		}

		if (player == NULL)
			return;
		float cx, cy;
		player->GetPosition(cx, cy);
		CGame* game = CGame::GetInstance();
		cx -= game->GetBackBufferWidth() / 2;
		int screenHeight = game->GetBackBufferHeight();
		game->SetCamPos(0, 0);
	}
	PurgeDeletedObjects();
}
