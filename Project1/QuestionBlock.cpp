
#include "QuestionBlock.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Utils.h"

using namespace std;

void CQuestionBlock::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    if(type==QUESTIONBLOCK_TYPE_EMPTY)
        animations->Get(ID_ANI_QUESTIONBLOCK_EMPTY)->Render(x, y);
    else
        animations->Get(ID_ANI_QUESTIONBLOCK)->Render(x, y);
    RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
    t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
    r = l + QUESTIONBLOCK_BBOX_WIDTH;
    b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::Reward(int level)
{
    if (this->type == QUESTIONBLOCK_TYPE_LEVEL_ITEM)
    {
        if (level == MARIO_LEVEL_SMALL)
        {
            CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
            CMushroom* mushroom = new CMushroom(x, y);
            currentScene->AddObject(mushroom);
            mushroom->EscapeBlock();
        }
        else if (level == MARIO_LEVEL_BIG)
        {
          CPlayScene* currentScene =(CPlayScene*) CGame::GetInstance()->GetCurrentScene();
          CLeaf* leaf = new CLeaf(x, y);
          currentScene->AddObject(leaf);
          leaf->EscapeBlock();
        }
    }
    else if (this->type == QUESTIONBLOCK_TYPE_COIN)
    {
        CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        CCoin* coin = new CCoin(x, y);
        currentScene->AddObject(coin);
        coin->EscapeBlock();
    }
    else if (this->type == QUESTIONBLOCK_TYPE_GREEN_MUSHROOM)
    {
        CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        CMushroom* mushroom = new CMushroom(x, y,2);
        currentScene->AddObject(mushroom);
        mushroom->EscapeBlock();
    }
    this->type = QUESTIONBLOCK_TYPE_EMPTY;
}
