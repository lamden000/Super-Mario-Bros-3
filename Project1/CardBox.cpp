#include "CardBox.h"

void CCardBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	changeTime += dt;
	if (changeTime >= CARD_BOX_CHANGE_TIME)
	{
		ChangeType();
		changeTime = 0;
	}
}

void  CCardBox::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	top = y - CARD_BOX_BBOX_HEIGHT / 2;
	left = x - CARD_BOX_BBOX_WIDTH / 2;
	right = left + CARD_BOX_BBOX_WIDTH;
	bottom = top + CARD_BOX_BBOX_HEIGHT;
}

void CCardBox::Render() {
	int spriteId;
	if (type == CARD_TYPE_EMPTY)
		spriteId = ID_SPRITE_CARD_EMPTY;
	else
		spriteId = ID_SPRITE_CARD_EMPTY+type;
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y,0.4,0.4);
	//RenderBoundingBox();
}
void CCardBox::ChangeType() {
	if (type == CARD_TYPE_EMPTY)
		return;
	type++;
	if (type > 3)
		type = 1;
}
int CCardBox::Reward() {
	int currentType = type;
	type = CARD_TYPE_EMPTY;
	return currentType;
}