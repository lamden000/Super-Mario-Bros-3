#pragma once

#include "GameObject.h"

class CSpawnPoint : public CGameObject
{
	string objectDetail;
	
	float height;
	float width;
public:
	CSpawnPoint(float l, float t, float r, float b, string objectDetail);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);

	string GetSpawnObjectDetai() { return objectDetail; };

	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
};