#pragma once
#include "GameObject.h"

#define ANIID 346
#define STAGE_SCALEX 1.2f
#define STAGE_SCALEY 1.2f
#define STAGE_WIDTH 300
#define STAGE_BBOX_WIDTH 495
#define STAGE_BBOX_HEIGHT 43

class CStage : public CGameObject
{
protected:

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CStage(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

