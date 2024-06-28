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
	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPipe::Render()
{
	if (this->length <= 0) return;
	CSprites* s = CSprites::GetInstance();
	float yy = y;

	s->Get(this->spriteIdBegin)->Draw(x, yy, PIPE_SCALEX, PIPE_SCALEY);
	yy += this->cellHeight;
	for (int i = 1; i < this->height - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(x, yy, PIPE_SCALEX, PIPE_SCALEY);
		yy += this->cellHeight;
	}
	if (height > 1)
	{
		if(orientation == PIPE_ORIENTATION_UP)
			s->Get(this->spriteIdEnd)->Draw(x, yy, PIPE_SCALEX, PIPE_SCALEY);
		else if (orientation == PIPE_ORIENTATION_DOWN)
			s->Get(this->spriteIdEnd)->Draw(x, yy, -PIPE_SCALEX, -PIPE_SCALEY);
	}
//	RenderBoundingBox();
}


void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellHeight_div_2 = this->cellHeight / 2;
	l = x - this->cellWidth / 2;
	t = y - cellHeight_div_2;
	r = l + this->cellWidth ;
	b = t + this->cellHeight * this->height;
}