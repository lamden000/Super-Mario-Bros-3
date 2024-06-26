#pragma once
#include "GoldBlock.h"

#define ID_SPRITE_ENABLE_BUTTON 99999
#define ID_SPRITE_UNABLE_BUTTON 99998

#define PSWITCH_BBOX_HEIGHT 16
#define PSWITCH_BBOX_WIDTH 16
#define PSWITCH_BBOX_UNABLE_HEIGHT 7

#define PSWITCH_REVEAL_SPEED_Y 0.1f
#define PSWITCH_REVEAL_GRAVITY 0.0003f

class CPSwitch : public CGameObject
{
protected:
    vector<CGoldBlock*> goldBlocks;
    bool enable;
    bool isRevealed;
    float ay;
public:
    CPSwitch(float x, float y);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void GetBrick(CGoldBlock* block) { goldBlocks.push_back(block); }
    int IsCollidable() { return enable && isRevealed && ay != 0; }
    int IsBlocking() { return enable; }
    void Render();
    void Reveal();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void BreakBrick();
    void OnCollisionWith(LPCOLLISIONEVENT e);
};