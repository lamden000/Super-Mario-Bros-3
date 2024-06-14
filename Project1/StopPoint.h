#pragma once

#include"GameObject.h"

#define STOP_POINT_BBOX_HEIGHT 3
#define STOP_POINT_BBOX_WIDTH 3

#define STOP_POINT_LEVEL_YELLOW_POINT 0
#define STOP_POINT_LEVEL_START 100
#define STOP_POINT_LEVEL_MUSHROOM_HOUSE 200
#define STOP_POINT_LEVEL_CARD 300
#define STOP_POINT_LEVEL_FORTRESS 400
#define STOP_POINT_LEVEL_CASTLE 500



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
