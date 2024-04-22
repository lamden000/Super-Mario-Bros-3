#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	state = -1;
	isDeleted = false;
}

void CGameObject::RenderBoundingBox()
{
    D3DXVECTOR3 cameraPos;
    CGame::GetInstance()->GetCamPos(cameraPos.x, cameraPos.y);

    RECT rect;

    float l, t, r, b;
    GetBoundingBox(l, t, r, b);
    rect.left = 0;
    rect.top = 0;
    rect.right = r - l;
    rect.bottom = b - t;

    // Vẽ bounding box với các tham số mặc định
    CGame::GetInstance()->Draw(x - cameraPos.x, y - cameraPos.y, CTextures::GetInstance()->Get(ID_TEX_BBOX), rect.left, rect.top, rect.right, rect.bottom, 0.25f);
}

CGameObject::~CGameObject()
{

}