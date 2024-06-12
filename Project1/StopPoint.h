#pragma once

#include"GameObject.h"

#define STOP_POINT_BBOX_HEIGHT 15
#define STOP_POINT_BBOX_WIDTH 15

#define STOP_POINT_LEVEL_YELLOW_POINT 0
#define STOP_POINT_LEVEL_START 100
#define STOP_POINT_LEVEL_MUSHROOM_HOUSE 200
#define STOP_POINT_LEVEL_CASTLE 300

#define ID_SPRITE_LEVEL_START 82100
#define ID_SPRITE_LEVEL_MUSHROOM_HOUSE 82101
#define ID_SPRITE_LEVEL_CASTLE 82102
#define ID_SPRITE_LEVEL_1 83001
#define ID_SPRITE_LEVEL_2 83002
#define ID_SPRITE_LEVEL_3 83003
#define ID_SPRITE_LEVEL_4 83004
#define ID_SPRITE_LEVEL_5 83005
#define ID_SPRITE_LEVEL_6 83006


class CStopPoint : public CGameObject
{
protected:
	vector<int> allowMoveDirection;
	int level;
public:
	CStopPoint(float x, float y,int level, vector<int> allowDirection) :CGameObject(x, y)
	{
		allowMoveDirection = allowDirection;
		this->level = level;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool isDirectionAllowed(int direction);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	int GetLevel() { return level; }
	void Render();
};
