#pragma once
#include "PlayScene.h"
#include "KeyEventHandlerForMario.h"

#define INTRO_ID 6
#define INTRO_BACKGROUND_COLOR_1 D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define INTRO_BACKGROUND_COLOR_2 D3DXCOLOR(247.0f / 255.0f, 215.0f / 255.0f, 164.0f / 255.0f, 1.0f)
#define INTRO_BACKGROUND_COLOR_3 D3DXCOLOR(247.0f / 255.0f - 0.05f, 215.0f / 255.0f - 0.05f, 164.0f / 255.0f - 0.05f, 1.0f)
#define CURTAIN_ID 2
#define LOGO_ID 4
#define LEAF_ID 5
#define STAGE_ID 3
#define LUIGI_ID 1

class CIntro :public CPlayScene {
protected:
	int action;
	DWORD introTimer;
	void _ParseSection_OBJECTS(string line);
public:
	CIntro(int id, LPCWSTR filePath);
	void Render();
	void AddObject(LPGAMEOBJECT object,int id);
	void Update(DWORD dt);
	void AutoRun(int action);
};
