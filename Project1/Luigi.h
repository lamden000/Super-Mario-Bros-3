#pragma once


#include "Mario.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"


#define LUIGI_WALKING_SPEED		0.08f
#define LUIGI_RUNNING_SPEED		0.2f

#define LUIGI_ACCEL_WALK_X	0.0005f
#define LUIGI_ACCEL_RUN_X	0.0007f

#define LUIGI_JUMP_SPEED_Y		0.6f
#define LUIGI_JUMP_RUN_SPEED_Y	0.9f

#define LUIGI_GRAVITY			0.002f

#define LUIGI_JUMP_DEFLECT_SPEED  1.0f

#define LUIGI_STATE_DIE				-10
#define LUIGI_STATE_IDLE			0
#define LUIGI_STATE_WALKING_RIGHT	100
#define LUIGI_STATE_WALKING_LEFT	200

#define LUIGI_STATE_JUMP			300
#define LUIGI_STATE_RELEASE_JUMP    301

#define LUIGI_STATE_RUNNING_RIGHT	400
#define LUIGI_STATE_RUNNING_LEFT	500

#define LUIGI_STATE_SIT				600
#define LUIGI_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

#define ID_ANI_LUIGI_IDLE_RIGHT 3000
#define ID_ANI_LUIGI_IDLE_LEFT 3001
#define ID_ANI_LUIGI_WALKING_RIGHT 3100
#define ID_ANI_LUIGI_WALKING_LEFT 3101

#define ID_ANI_LUIGI_RUNNING_RIGHT 2200
#define ID_ANI_LUIGI_RUNNING_LEFT 2201

#define ID_ANI_LUIGI_JUMP_WALK_RIGHT 2300
#define ID_ANI_LUIGI_JUMP_WALK_LEFT 2301

#define ID_ANI_LUIGI_JUMP_RUN_RIGHT 2400
#define ID_ANI_LUIGI_JUMP_RUN_LEFT 2401

#define ID_ANI_LUIGI_SIT_RIGHT 2500
#define ID_ANI_LUIGI_SIT_LEFT 2501

#define ID_ANI_LUIGI_BRACE_RIGHT 2600
#define ID_ANI_LUIGI_BRACE_LEFT 2601

#define ID_ANI_LUIGI_DIE 9999

// SMALL LUIGI
#define ID_ANI_LUIGI_SMALL_IDLE_RIGHT 2700
#define ID_ANI_LUIGI_SMALL_IDLE_LEFT 2701

#define ID_ANI_LUIGI_SMALL_WALKING_RIGHT 2800
#define ID_ANI_LUIGI_SMALL_WALKING_LEFT 2801

#define ID_ANI_LUIGI_SMALL_RUNNING_RIGHT 2900
#define ID_ANI_LUIGI_SMALL_RUNNING_LEFT 2901

#define ID_ANI_LUIGI_SMALL_BRACE_RIGHT 3000
#define ID_ANI_LUIGI_SMALL_BRACE_LEFT 3001

#define ID_ANI_LUIGI_SMALL_JUMP_WALK_RIGHT 3100
#define ID_ANI_LUIGI_SMALL_JUMP_WALK_LEFT 3101

#define ID_ANI_LUIGI_SMALL_JUMP_RUN_RIGHT 3200
#define ID_ANI_LUIGI_SMALL_JUMP_RUN_LEFT 3201

#pragma endregion

#define GROUND_Y 160.0f




#define	LUIGI_LEVEL_SMALL	1
#define	LUIGI_LEVEL_BIG		2

#define LUIGI_BIG_BBOX_WIDTH  14
#define LUIGI_BIG_BBOX_HEIGHT 24
#define LUIGI_BIG_SITTING_BBOX_WIDTH  14
#define LUIGI_BIG_SITTING_BBOX_HEIGHT 16

#define LUIGI_SIT_HEIGHT_ADJUST ((LUIGI_BIG_BBOX_HEIGHT-LUIGI_BIG_SITTING_BBOX_HEIGHT)/2)

#define LUIGI_SMALL_BBOX_WIDTH  13
#define LUIGI_SMALL_BBOX_HEIGHT 12


#define LUIGI_UNTOUCHABLE_TIME 2500

class CLuigi : public CMario
{
protected:
	int GetAniIdBig();
	int GetAniIdSmall();
public:
	CLuigi(float x, float y) : CMario(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = LUIGI_GRAVITY;
		level = LUIGI_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		nx = 1;
	}
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != LUIGI_STATE_DIE);
	}

	int IsBlocking() { return (state != LUIGI_STATE_DIE && untouchable == 0); }
	void JumpDeflect();

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};