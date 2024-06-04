#pragma once
#include "Koopas.h"

#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_BOUNCING_SPEED 0.23f;
#define KOOPAS_JUMP_COOLDOWN 1500
#define KOOPAS_JUMP_SPEED 0.4f

#define GREENKOOPAS_BBOX_WIDTH 10
#define GREENKOOPAS_BBOX_HEIGHT 25
#define GREENKOOPAS_BBOX_HEIGHT_SHELL 11


#define GREENKOOPAS_LEVEL_NORMAL 1
#define GREENKOOPAS_LEVEL_WINGS 2

#define GREENKOOPAS_STATE_WALKING 100
#define GREENKOOPAS_STATE_REVIVING 200
#define KOOPAS_STATE_SHELL 300
#define GREENKOOPAS_STATE_JUMP	500

#define ID_ANI_GREENKOOPAS_WALKING_RIGHT 30
#define ID_ANI_GREENKOOPAS_WALKING_RIGHT_WITH_WINGS 33
#define ID_ANI_GREENKOOPAS_JUMP_RIGHT 36
#define ID_ANI_GREENKOOPAS_WALKING_LEFT 31
#define ID_ANI_GREENKOOPAS_WALKING_LEFT_WITH_WINGS 34
#define ID_ANI_GREENKOOPAS_JUMP_LEFT 35
#define ID_ANI_GREENKOOPAS_REVIVING 37
#define ID_ANI_GREENKOOPAS_SHELL 39
#define ID_ANI_GREENKOOPAS_SHELL_BOUNCING 38

#define GREENKOOPAS_SHELL_TIME  4000
#define GREENKOOPAS_REVIVE_TIME  2000

#define GREENKOOPAS_SCALEX 0.35f
#define GREENKOOPAS_SCALEY 0.35f

class CGreenKoopas : public CBrownKoopas
{
protected:
	ULONGLONG jump_start;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGreenKoopas(float x, float y, int level):CBrownKoopas(x, y, level) { jump_start = 1500; };
	virtual void SetState(int state, float nx = 0);
	virtual void Hop();
};



