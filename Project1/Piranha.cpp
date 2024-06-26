#include "Piranha.h"

void CPiranha::Grow(DWORD dt, float mario_x, float mario_y)
{
    float growHeight;
    if (type == PIRANHA_TYPE_GREEN)
        growHeight = GREEN_VENUS_GROWN_HEIGHT;
    else
        growHeight = RED_VENUS_GROWN_HEIGHT;

    if (abs(y_start - y) >= growHeight)
        vy = -vy;
}
void CPiranha::Render()
{
    if (type == PIRANHA_TYPE_GREEN)
        CAnimations::GetInstance()->Get(ID_ANI_PIRANHA_GREEN)->Render(x,y,0.3,0.3);
}