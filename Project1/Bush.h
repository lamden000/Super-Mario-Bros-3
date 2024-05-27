#pragma once

#include "GameObject.h"

#define  BUSH_SCALEX 0.4
#define  BUSH_SCALEY 0.4

#define  BUSH_WIDTH	21
#define  BUSH_HEIGTH 18

class CBush : public CGameObject
{
protected:
	int height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CBush(float x, float y,
		 int height,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->height = height;
		this->cellWidth =  BUSH_WIDTH;
		this->cellHeight =  BUSH_HEIGTH;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}
	int  IsCollidable() { return 0; }
	void Update(DWORD dt) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	void RenderBoundingBox();
};

