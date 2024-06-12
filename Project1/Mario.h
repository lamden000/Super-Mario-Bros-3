#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.0004f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define RACOON_MARIO_FLY_SPEED_Y 0.35f

#define MARIO_GRAVITY			0.0015f
#define RACOON_MARIO_FALLING_SPEED	0.08f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID
//BIG
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_HOLD_OBJECT_RIGHT 2000
#define ID_ANI_MARIO_HOLD_OBJECT_LEFT 2001

#define ID_ANI_MARIO_HOLD_OBJECT_MOVING_RIGHT 2100
#define ID_ANI_MARIO_HOLD_OBJECT_MOVING_LEFT 2101

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_OBJECT_RIGHT 1700
#define ID_ANI_MARIO_SMALL_HOLD_OBJECT_LEFT 1701

#define ID_ANI_MARIO_SMALL_HOLD_OBJECT_MOVING_RIGHT 1800
#define ID_ANI_MARIO_SMALL_HOLD_OBJECT_MOVING_LEFT 1801

//RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 430
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 431

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 530
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 531

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 630
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 631

#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 730
#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 731

#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 830
#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 831

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 930
#define ID_ANI_MARIO_RACOON_SIT_LEFT 931

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 1030
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 1031

#define ID_ANI_MARIO_JUMP_FALLING_RIGHT 1040
#define ID_ANI_MARIO_FALLING_RIGHT 1041

#define ID_ANI_MARIO_JUMP_FALLING_LEFT 1050
#define ID_ANI_MARIO_FALLING_LEFT 1051

#define ID_ANI_RACOON_MARIO_DIE 939

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON		3

#define MARIO_BIG_BBOX_WIDTH  11
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_ALOW_FLY_RUN_TIME 2000
#define MARIO_MAX_FLY_TIME 3500
#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
protected:
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	bool isHolding;
	int level;
	int untouchable;

	DWORD runTime;
	DWORD flyTime;
	LPGAMEOBJECT holdedObject;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	D3DXVECTOR2 moveDirection;
	D3DXVECTOR2 jumpDirection;


	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithLuigi(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawnPoint(LPCOLLISIONEVENT e);
	void OnCollisionWithQestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y,int level= MARIO_LEVEL_SMALL) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		this->level = level;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		isHolding = false;
		nx = 1;
		runTime = 0;
		holdedObject = NULL;
		flyTime = 0;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void Hold() { isHolding = true; }
	void SetHoldedObject(LPGAMEOBJECT object) { this->holdedObject = object; };
	void HoldObject();

	LPGAMEOBJECT GetHoldedObject() { return holdedObject; }
	void ReleaseHold();

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	DWORD GetRunTime() { return runTime; }
	DWORD GetFlyTime() { return flyTime; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void DecreaseLevel();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
