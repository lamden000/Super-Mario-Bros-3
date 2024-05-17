#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBLOCK 12341
#define ID_ANI_QUESTIONBLOCK_EMPTY 12381
#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16
#define QUESTIONBLOCK_TYPE_EMPTY 0
#define QUESTIONBLOCK_TYPE_COIN 1
#define QUESTIONBLOCK_TYPE_LEVEL_ITEM 2
#define QUESTIONBLOCK_TYPE_GREEN_MUSHROOM 3

class CQuestionBlock : public CGameObject {
protected:
	int type;
public:
	CQuestionBlock(float x, float y,int type=1) : CGameObject(x, y) 
	{
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Reward();
};