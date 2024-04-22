#include "Intro.h"

CIntro::CIntro(int id, LPCWSTR filePath) :
	CPlayScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}

void CIntro::Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, INTRO_BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

void CIntro::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	static bool waitFinished = false;
	WaitForIntro(dt, 1000, waitFinished);
	if (!waitFinished) return;

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
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
