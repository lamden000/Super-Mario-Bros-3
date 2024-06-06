#pragma once

#include "GameObject.h"
#include "Animations.h"

#define ID_SPRITE_UI 81000
#define ID_SPRITE_POINTER 81001
#define MODE_1_PLAYER 1
#define MODE_2_PLAYER 2

class CMenuUI : public CGameObject {
protected:
	float pointer_x;
	float pointer_y;
	int mode;
public:
	CMenuUI(float x,float y) :CGameObject(x,y)
	{
		pointer_x = x-60;
		pointer_y = y-17;
		mode = MODE_1_PLAYER;
	}
	void Render();
	void SetMode();
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};