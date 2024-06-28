#pragma once


#include "GameObject.h"

#define PORTAL_MAX_TRAVEL_TIME 1000
/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	float tele_x;
	float tele_y;
	bool isActive;

	float width;
	float height;
public:
	CPortal(float l, float t, float r, float b, float tele_x,float tele_y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetAtive(bool isActive) { this->isActive = isActive; }

	int IsBlocking() { return 0; }
};