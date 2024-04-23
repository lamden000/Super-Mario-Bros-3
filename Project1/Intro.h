#pragma once
#include "PlayScene.h"
#include "SampleKeyEventHandler.h"

#define INTRO_ID 6
#define INTRO_BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define MARIO_ID 0
#define CURTAIN_ID 2
#define LUIGI_ID 1
#define ACTION_1 1
#define ACTION_2 2
#define ACTION_3 3
#define ACTION_4 4

class CIntro :public CPlayScene {
protected:
	int action;
	void _ParseSection_OBJECTS(string line);
public:
	CIntro(int id, LPCWSTR filePath);
	void Render();
	void Update(DWORD dt);
	void WaitForIntro(DWORD dt, DWORD introDuration, bool& waitFinished);
	void AutoRun(int action);
};
