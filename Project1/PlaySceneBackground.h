#pragma once
#include"GameObject.h"
class CPlaySceneBackground : public CGameObject {
protected:
	int sprite_id;
	float scale_x;
	float scale_y;
public:
	CPlaySceneBackground(float x, float y, int sprteId, float scale_x, float scale_y) :CGameObject(x, y) {
		this->sprite_id = sprteId;
		this->scale_x = scale_x;
		this->scale_y = scale_y;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};
