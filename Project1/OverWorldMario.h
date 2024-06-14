#pragma once
#include "GameObject.h"
#include "StopPoint.h"

#define OVERWORLD_MARIO_SPEED 0.1f
#define	ID_ANI_OVERWORLD_MARIO 90105

#define OVERWORLDMARIO_BBOX_WIDTH	3
#define OVERWORLDMARIO_BBOX_HEIGHT 3

#define OVERWORLD_MARIO_STATE_STAND_STILL 0
#define OVERWORLD_MARIO_STATE_GO_UP 100
#define OVERWORLD_MARIO_STATE_GO_RIGHT 200
#define OVERWORLD_MARIO_STATE_GO_LEFT 300
#define OVERWORLD_MARIO_STATE_GO_DOWN 400

class COverWorldMario : public CGameObject
{
protected:
	CStopPoint* currentStopPoint;
public:
	COverWorldMario(float x,float y):CGameObject(x,y){
		currentStopPoint = NULL;
		vx = 0;
		vy = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	void SetCurrentStopPoint(CStopPoint* stopPoint) { 
		if(stopPoint!=NULL)
			stopPoint->GetPosition(x, y);
		currentStopPoint = stopPoint;
	}
	CStopPoint* GetCurrentStopPoint() { return currentStopPoint; }
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};