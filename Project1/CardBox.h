#pragma once

#include "GameObject.h"

#define CARD_BOX_CHANGE_TIME 200

#define CARD_BOX_BBOX_HEIGHT 28
#define CARD_BOX_BBOX_WIDTH 23

#define ID_SPRITE_CARD_EMPTY 46873 
#define ID_SPRITE_CARD_MUSHROOM   46874
#define ID_SPRITE_CARD_FLOWER  46875
#define ID_SPRITE_CARD_START  46875

#define CARD_TYPE_EMPTY 0
#define CARD_TYPE_MUSHROOM 1
#define CARD_TYPE_FLOWER 2
#define CARD_TYPE_START 3

class CCardBox : public CGameObject {
protected:
	int changeTime;
	int type;
public:
	CCardBox(float x,float y){
		type = CARD_TYPE_MUSHROOM;
		changeTime = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 1; }
	int Reward();
	void ChangeType();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};