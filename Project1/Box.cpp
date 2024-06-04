#include "Box.h"

void CBox::Render()
{
    CSprites* sprites = CSprites::GetInstance();
    float scaleX, scaleY;
    scaleX = -1;
    scaleY = -1;
    int spriteId=-1;
    if (type == BOX_WHITE)
    {
        scaleY = height / SPRITE_BOX_WHITE_HEIGHT;
        scaleX = width / SPRITE_BOX_WHITE_WIDTH;
        spriteId = ID_SPRITE_BOX_WHITE;
    }
    else if (type == BOX_BLUE)
    {
        scaleY = height / SPRITE_BOX_BLUE_HEIGHT;
        scaleX = width / SPRITE_BOX_BLUE_WIDTH;
        spriteId = ID_SPRITE_BOX_BLUE;
    }
    else if (type == BOX_PINK)
    {
        scaleY = height / SPRITE_BOX_PINK_HEIGHT;
        scaleX= width / SPRITE_BOX_PINK_WIDTH;
        spriteId = ID_SPRITE_BOX_PINK;
    }
    else if (type == BOX_GREEN)
    {
        scaleY= height / SPRITE_BOX_GREEN_HEIGHT;
        scaleX = width / SPRITE_BOX_GREEN_WIDTH;
        spriteId = ID_SPRITE_BOX_GREEN;
    }
    sprites->Get(ID_SPRITE_BOX_SHADOW)->Draw(x + width / 2, y + height /5.5, 0.4, scaleY);
    sprites->Get(spriteId)->Draw(x, y, scaleX, scaleY);  
   // RenderBoundingBox();
}

void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - width / 2;
    t = y - height / 2;
    r = l + width;
    b = t + height;
}

int CBox::IsDirectionColliable(float nx, float ny)
{
    if (nx == 0 && ny == -1) return 1;
    else return 0;
}
