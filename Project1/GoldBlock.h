#pragma once

#include"QuestionBlock.h"

#define ID_ANI_GOLD_BRICK 10001
#define ID_ANI_GOLD_BLOCK_EMPTY 12381

#define GOLD_BLOCK_GRAVITY 0.001;

#define GOLD_BLOCK_BBOX_HEIGHT 15
#define GOLD_BLOCK_BBOX_WIDTH 15

#define GOLD_BLOCK_TYPE_GREEN_MUSHROOM 2
#define GOLD_BLOCK_TYPE_COIN 1
#define GOLD_BLOCK_TYPE_BREAKABLE 0

#define P_SWITCH_TIME 8000
class CGoldBlock : public CQuestionBlock
{
protected:
	bool isEmpty;
	float ay;
	float start_y;
	int p_switch_time;
	bool generated_coin;
public:
	CGoldBlock(float x, float y, int type) :CQuestionBlock(x, y,type) {
		isEmpty = false;
		ay = GOLD_BLOCK_GRAVITY;
		start_y = y;
		p_switch_time = 0;
		generated_coin = false;
	}
	int IsBlocking() {	return 1;}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Reward();
	void TurnIntoCoin();
};