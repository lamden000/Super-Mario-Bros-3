#include"PlaySceneBackground.h"
void CPlaySceneBackground::Render() {
	CSprites::GetInstance()->Get(sprite_id)->Draw(x, y, scale_x, scale_y);
}