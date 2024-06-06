#include"MenuUI.h"
void CMenuUI::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_UI)->Draw(x,y);
	CSprites::GetInstance()->Get(ID_SPRITE_POINTER)->Draw(pointer_x, pointer_y);
}
void CMenuUI::SetMode() {
	if (mode == MODE_1_PLAYER)
	{
		mode++;
		pointer_y += 16;
	}
	else 
	{
		mode--;
		pointer_y -= 16;
	}
}
