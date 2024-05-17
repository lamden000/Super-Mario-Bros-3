#include <cstdlib>

#include "FireBall.h"
#include "PlayScene.h"


CFireBall::CFireBall(float x, float y) :CGameObject(x, y)
{
    CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    float mario_x, mario_y;
    mario->GetPosition(mario_x, mario_y);
    x_start = x;
    y_start = y;

    if(mario_x<x)
         vx = -FIREBALL_SPEED;
    else
        vx = FIREBALL_SPEED;

    if (mario_y < y)
        t = FIREBALL_HIGH_TRAJECTORY_T;
    else
    {
        if (mario_y  > y_start+ FIREBALL_LOW_TRAJECTORY_RANGE_Y && abs(mario_x-x_start) <  FIREBALL_LOW_TRAJECTORY_RANGE_X)
            t = FIREBALL_LOW_TRAJECTORY_T;
        else
            t = FIREBALL_MID_TRAJECTORY_T;
    }
\
}

void CFireBall::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(ANI_ID_FIREBALL)->Render(x, y,FIREBALL_SCALEX,FIREBALL_SCALEY);
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - FIREBALL_BBOX_WIDTH / 2;
    t = y - FIREBALL_BBOX_HEIGHT / 2;
    r = l + FIREBALL_BBOX_WIDTH;
    b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

    x += vx * dt;
    if(vx<0)
        y = t * (x - x_start) + y_start;
    else
        y = -t * (x - x_start) + y_start;
    CCollision::GetInstance()->Process(this, dt, coObjects);
}