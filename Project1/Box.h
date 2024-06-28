#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITE_BOX_WHITE 400
#define ID_SPRITE_BOX_BLUE 401
#define ID_SPRITE_BOX_PINK 403
#define ID_SPRITE_BOX_GREEN 402
#define ID_SPRITE_BOX_SHADOW 405
#define ID_SPRITE_BOX_SCREW 406

#define BOX_GREEN 1
#define BOX_WHITE 2
#define BOX_PINK 3
#define BOX_BLUE 4

#define SPRITE_BOX_WHITE_HEIGHT 140
#define SPRITE_BOX_WHITE_WIDTH 150

#define SPRITE_BOX_BLUE_HEIGHT 140
#define SPRITE_BOX_BLUE_WIDTH 152

#define SPRITE_BOX_PINK_HEIGHT 140
#define SPRITE_BOX_PINK_WIDTH  151

#define SPRITE_BOX_GREEN_HEIGHT 140
#define SPRITE_BOX_GREEN_WIDTH 	149

#define SPRITE_BOX_SHADOW_HEIGHT 97
#define SPRITE_BOX_SHADOW_WIDTH 29


class CBox: public CGameObject {
protected:
	float height;
	float width;
	int type;
public:
	CBox(float x, float y,float height,float width,int type) : CGameObject(x, y) {
		this->height = height;
		this->width = width;
		this->type = type;
	}
	int IsDirectionColliable(float nx, float ny);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};