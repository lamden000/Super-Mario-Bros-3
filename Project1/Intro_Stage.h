#pragma once
#include "GameObject.h"

#define ANIID 346
#define STAGE_SCALEX 0.3f
#define STAGE_SCALEY 0.3f
#define STAGE_BBOX_TOP 165
#define STAGE_BBOX_LEFT 0
#define STAGE_BBOX_OFFSET 700

class CStage : public CGameObject
{
protected:

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
public:
	CStage(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

