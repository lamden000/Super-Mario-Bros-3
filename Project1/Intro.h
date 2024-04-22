#pragma once
#include "PlayScene.h"
#include "SampleKeyEventHandler.h"

#define INTRO_ID 6
#define INTRO_BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)

class CIntro :public CPlayScene {
public:
	CIntro(int id, LPCWSTR filePath);
	void Render();
	void Update(DWORD dt);
	void WaitForIntro(DWORD dt, DWORD introDuration, bool& waitFinished);
};
