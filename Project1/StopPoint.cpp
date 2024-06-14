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

}
void CStopPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - STOP_POINT_BBOX_WIDTH / 2;
	top = y - STOP_POINT_BBOX_HEIGHT / 2;
	right = left + STOP_POINT_BBOX_WIDTH;
	bottom = top + STOP_POINT_BBOX_HEIGHT;
}