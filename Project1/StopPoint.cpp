#include "StopPoint.h"

bool CStopPoint::isDirectionAllowed(int direction)
{
	for (int i = 0; i < allowMoveDirection.size(); i++)
		if (direction == allowMoveDirection[i])
			return true;
	return false;
}

void CStopPoint::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	int spriteId = -1;
	switch (level)
	{
	case STOP_POINT_LEVEL_CASTLE:
		spriteId = ID_SPRITE_LEVEL_CASTLE;
		break;
	case STOP_POINT_LEVEL_MUSHROOM_HOUSE:
		spriteId = ID_SPRITE_LEVEL_MUSHROOM_HOUSE;
		break;
	case STOP_POINT_LEVEL_START:
		spriteId = ID_SPRITE_LEVEL_START;
		break;
	case 1:
		spriteId=ID_SPRITE_LEVEL_1;
		break;
	case 2:
		spriteId = ID_SPRITE_LEVEL_3;
		break;
	case 3:
		spriteId = ID_SPRITE_LEVEL_3;
		break;
	case 4:
		spriteId = ID_SPRITE_LEVEL_4;
		break;
	case 5:
		spriteId = ID_SPRITE_LEVEL_5;
		break;
	case 6:
		spriteId = ID_SPRITE_LEVEL_6;
		break;
	}
	if(spriteId!=-1)
		sprites->Get(spriteId)->Draw(x, y,0.3,0.3);
	RenderBoundingBox();
}
void CStopPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - STOP_POINT_BBOX_WIDTH / 2;
	top = y - STOP_POINT_BBOX_HEIGHT / 2;
	right = left + STOP_POINT_BBOX_WIDTH;
	bottom = top + STOP_POINT_BBOX_HEIGHT;
}