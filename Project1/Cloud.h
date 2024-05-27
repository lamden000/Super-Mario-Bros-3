#pragma once
#include "GameObject.h"

#define CLOUD_ANIID 10002
#define CLOUD_SCALEX 0.3
#define CLOUD_SCALEY 0.3

class CCloud : public CGameObject
{
protected:
public:
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	void Render();
	CCloud(float x, float y);
};


