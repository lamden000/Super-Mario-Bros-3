#include "OverWorld.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Utils.h"

#include "OverWorldKeyEventHandler.h"
#include "OverWorldMario.h"
#include "OverWorldUI.h"
#include "StopPoint.h"

#define ID_ANI_OVERWORLD_TREE 90106

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
	
	CSprites::GetInstance()->Get(ID_SPRITE_OVERWORLD_BACKGROUND)->Draw(150,86,0.25,0.23);

	RenderTree();

	for (int i = objects.size() - 1; i >= 0; i--)
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

void COverWorld::RenderTree() {
	CAnimation* treeAnimation = CAnimations::GetInstance()->Get(ID_ANI_OVERWORLD_TREE);

	treeAnimation->Render(42, 21, 0.35, 0.35);
	treeAnimation->Render(58, 21, 0.35, 0.35);
	treeAnimation->Render(74, 21, 0.35, 0.35);
	treeAnimation->Render(42, 38, 0.35, 0.35);
	treeAnimation->Render(58, 38, 0.35, 0.35);
	treeAnimation->Render(74, 38, 0.35, 0.35);

	treeAnimation->Render(214, 36, 0.35, 0.35);
	treeAnimation->Render(198, 36, 0.35, 0.35);
	treeAnimation->Render(182, 36, 0.35, 0.35);

	treeAnimation->Render(42, 71, 0.35, 0.35);
	treeAnimation->Render(58, 71, 0.35, 0.35);
	treeAnimation->Render(74, 71, 0.35, 0.35);
	treeAnimation->Render(42, 88, 0.35, 0.35);
	treeAnimation->Render(58, 88, 0.35, 0.35);
	treeAnimation->Render(74, 88, 0.35, 0.35);
	treeAnimation->Render(42, 105, 0.35, 0.35);

	treeAnimation->Render(110, 38, 0.35, 0.35);
	treeAnimation->Render(126, 38, 0.35, 0.35);
	treeAnimation->Render(142, 38, 0.35, 0.35);
	treeAnimation->Render(110, 55, 0.35, 0.35);
	treeAnimation->Render(126, 55, 0.35, 0.35);
	treeAnimation->Render(142, 55, 0.35, 0.35);
	treeAnimation->Render(110, 71, 0.35, 0.35);
	treeAnimation->Render(126, 71, 0.35, 0.35);
	treeAnimation->Render(142, 71, 0.35, 0.35);

	treeAnimation->Render(126, 100, 0.35, 0.35);
	treeAnimation->Render(142, 100, 0.35, 0.35);
	treeAnimation->Render(158, 100, 0.35, 0.35);

	treeAnimation->Render(246, 21, 0.35, 0.35);
	treeAnimation->Render(262, 21, 0.35, 0.35);
	treeAnimation->Render(246, 38, 0.35, 0.35);
	treeAnimation->Render(262, 38, 0.35, 0.35);
	treeAnimation->Render(246, 55, 0.35, 0.35);
	treeAnimation->Render(262, 55, 0.35, 0.35);
	treeAnimation->Render(246,71, 0.35, 0.35);
	treeAnimation->Render(262, 71, 0.35, 0.35);

	treeAnimation->Render(230, 71, 0.35, 0.35);
	treeAnimation->Render(214, 71, 0.35, 0.35);
	treeAnimation->Render(198, 71, 0.35, 0.35);
	treeAnimation->Render(182, 71, 0.35, 0.35);

	treeAnimation->Render(198, 87, 0.35, 0.35);
	treeAnimation->Render(182, 87, 0.35, 0.35);

	treeAnimation->Render(262, 88, 0.35, 0.35);
	treeAnimation->Render(262, 105, 0.35, 0.35);
	treeAnimation->Render(262, 122, 0.35, 0.35);
	treeAnimation->Render(262, 139, 0.35, 0.35);
	treeAnimation->Render(262,156, 0.35, 0.35);

}