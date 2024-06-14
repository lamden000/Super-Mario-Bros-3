#pragma once
#include "PlayScene.h"
#include "KeyEventHandlerForMario.h"

#define OVERWORLD_BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define ID_SPRITE_OVERWORLD_BACKGROUND 81000
#define OVERWORLD_ID 7
#define ID_SPRITE_HORIONTAL_ROAD 84000
#define ID_SPRITE_VERTICAL_ROAD 84001

class COverWorld :public CPlayScene {
protected:
	void _ParseSection_OBJECTS(string line);
public:
	COverWorld(int id, LPCWSTR filePath);
	void Render();
	void Update(DWORD dt);
	//void AddObject(LPGAMEOBJECT object, int id);
};

