#include "Pipe.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPipe::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y - this->cellHeight /2 + rect.bottom / 2;
	if (orientation == PIPE_ORIENTATION_HORIZONTAL)
	{
		CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
	}
	else {
		CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
	}
}

void CPipe::Render()
{
	if (this->length <= 0) return;
	CSprites* s = CSprites::GetInstance();

	if (orientation == PIPE_ORIENTATION_VERTICAL)
	{
		float yy = y;

		s->Get(this->spriteIdBegin)->Draw(x, yy, PIPE_SCALEX, PIPE_SCALEY);
		yy += this->cellHeight;
		for (int i = 1; i < this->height - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(x, yy, PIPE_SCALEX, PIPE_SCALEY);
			yy += this->cellHeight;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd)->Draw(x, yy, PIPE_SCALEX, PIPE_SCALEY);
	}
	else {
		float xx = x;

		s->Get(this->spriteIdBegin)->Draw(xx, y, PIPE_SCALEX, PIPE_SCALEY);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMiddle)->Draw(xx, y,PIPE_SCALEX, PIPE_SCALEY);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd)->Draw(xx, y,PIPE_SCALEX,PIPE_SCALEY);
	}
	RenderBoundingBox();
}


void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (orientation == PIPE_ORIENTATION_HORIZONTAL)
	{
		float cellWidth_div_2 = this->cellWidth / 2;
		l = x - cellWidth_div_2;
		t = y - this->cellHeight / 2;
		r = l + this->cellWidth * this->length;
		b = t + this->cellHeight;
	}
	else {
		float cellHeight_div_2 = this->cellHeight / 2;
		l = x - this->cellWidth / 2;
		t = y - cellHeight_div_2;
		r = l + this->cellWidth ;
		b = t + this->cellHeight * this->height;
	}
}