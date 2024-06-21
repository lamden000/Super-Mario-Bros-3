#include <cstdlib>

#include "Venus.h"
#include "Playscene.h"
#include "FireBall.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 202

void CVenus::Render()
{
    CAnimations* animations = CAnimations::GetInstance();

    CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    float mario_x, mario_y;
    mario->GetPosition(mario_x, mario_y);
    int aniID = -1;
    if (type == VENUS_TYPE_GREEN)
    {
        if (x < mario_x)
        {
            if (y < mario_y)
                aniID = ID_ANI_GREEN_VENUS_LOOK_UP_RIGHT;
            else  
                aniID = ID_ANI_GREEN_VENUS_LOOK_DOWN_RIGHT;
        }
        else {
            if (y < mario_y)
                aniID = ID_ANI_GREEN_VENUS_LOOK_UP_LEFT;
            else 
                aniID = ID_ANI_GREEN_VENUS_LOOK_DOWN_LEFT;
        }
      
    }
    else {

        if (x < mario_x)
        {
            if (y < mario_y)
                aniID = ID_ANI_RED_VENUS_LOOK_UP_RIGHT;
            else
                aniID = ID_ANI_RED_VENUS_LOOK_DOWN_RIGHT;
        }
        else {
            if (y < mario_y)
                aniID = ID_ANI_RED_VENUS_LOOK_UP_LEFT;
            else
                aniID = ID_ANI_RED_VENUS_LOOK_DOWN_LEFT;
        }
    }
    animations->Get(aniID)->Render(x, y, VENUS_SCALEX, VENUS_SCALEY);
   // RenderBoundingBox();
}

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

    CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
    float mario_x, mario_y;
    mario->GetPosition(mario_x, mario_y);
    if (abs(mario_x - x) > SCREEN_WIDTH/2 || abs(mario_y - y) > SCREEN_HEIGHT/2)
        return;
    Grow(dt,mario_x,mario_y);
    x += vx * dt;
    y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CVenus::Shoot(DWORD dt)
{
    shooting_Time -= dt;

    static bool shot = false;
    if (shooting_Time <= VENUS_SHOOTING_TIME / 2 && !shot)
    {
        CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        float fireBall_y = y - 5;
        CFireBall* fireBall = new CFireBall(x, fireBall_y);
        scene->AddObject(fireBall, 2);
        shot = true;
    }

    if (shooting_Time > 0)
    {
        vy = 0;
    }
    else {
        vy = VENUS_GROW_SPEED;
        shot = false;
    }
}

void CVenus::Grow(DWORD dt,float mario_x,float mario_y)
{
    float growHeight;
    if (type == VENUS_TYPE_GREEN)
        growHeight = GREEN_VENUS_GROWN_HEIGHT;
    else 
        growHeight = RED_VENUS_GROWN_HEIGHT;

    if (abs(y_start - y) >= growHeight)
    {
        vy = -vy;
        if (y < y_start)
        {
            Shoot(dt);
            isGoingUp = false;
        }
        else {
            shooting_Time = VENUS_SHOOTING_TIME;
            isGoingUp = true;
        }
    }
    else if ((x - VENUS_BBOX_WIDTH < mario_x && mario_x < x + VENUS_BBOX_WIDTH) && y > (y_start + GREEN_VENUS_BBOX_HEIGHT / 2))
    {
        vy = 0;
    }
    else {
        if (isGoingUp)
            vy = -VENUS_GROW_SPEED;
        else
            vy = VENUS_GROW_SPEED;
    }

}

void CVenus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    if (type == VENUS_TYPE_GREEN)
    {
        t = y - GREEN_VENUS_BBOX_HEIGHT / 2;
        b = t + GREEN_VENUS_BBOX_HEIGHT;
    }
    else {
        t = y - RED_VENUS_BBOX_HEIGHT / 2;
        b = t + RED_VENUS_BBOX_HEIGHT;
    }
    l = x - VENUS_BBOX_WIDTH / 2;
    r = l + VENUS_BBOX_WIDTH;
  
}