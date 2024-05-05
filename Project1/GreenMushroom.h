#pragma once
#include "Mushroom.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.03f
#define MUSHROOM_ESCAPE_BLOCK_SPEED 0.3f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_DIE_TIMEOUT 500

#define ID_ANI_GREEN_MUSHROOM 2225

class CGreenMushroom :public CMushroom {

public:
	CGreenMushroom(float x, float y);
};
