#include "Bush.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CBush::RenderBoundingBox()
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
	float yy = y - this->cellHeight / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CBush::Render()
{
	if (this->height <= 0) return;
	CSprites* s = CSprites::GetInstance();
	float yy = y;

	s->Get(this->spriteIdBegin)->Draw(x, yy, BUSH_SCALEX, BUSH_SCALEY);
	yy -= this->cellHeight;
	for (int i = this->height -2; i >0; i--)
	{
		s->Get(this->spriteIdMiddle)->Draw(x, yy, BUSH_SCALEX, BUSH_SCALEX);
		yy -= this->cellHeight;
	}
	if (height > 1)
		s->Get(this->spriteIdEnd)->Draw(x, yy, BUSH_SCALEX, BUSH_SCALEX);
}
