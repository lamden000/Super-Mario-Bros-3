#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITE_MAIN_BOARD 80000
#define ID_SPRITE_NUMBER_BASE 90000

#define ID_SPRITE_WHITE_ARROW 90100
#define ID_SPRITE_BLACK_ARROW 90101
#define ID_SPRITE_WHITE_P 90102
#define ID_SPRITE_BLACK_P 90103

#define UI_CAMERA_DISTANCE_X 90
#define UI_CAMERA_DISTANCE_Y 185

class CInGameUI : public CGameObject {
public:
	CInGameUI() { };
	void Render();
	int IsBlocking() { return 0; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b){}
	vector<int> getDigits(DWORD number);
	int getMarioRunningTimeSection(DWORD runTime);
};