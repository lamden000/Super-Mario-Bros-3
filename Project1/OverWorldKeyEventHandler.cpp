#include "OverWorldKeyEventHandler.h"

#include "Game.h"
#include "OverWorld.h"
#include "OverWorldMario.h"

void COverWorldKeyEventHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	COverWorld* scene = (COverWorld*)game->GetCurrentScene();
	COverWorldMario* mario = (COverWorldMario*)scene->GetPlayer();
	CStopPoint* currentStopPoint = mario->GetCurrentStopPoint();
	if (currentStopPoint != NULL)
	{
		switch (KeyCode)
		{
			case DIK_W:
			{
				int level = currentStopPoint->GetLevel();
				if (level == 1)
				{
					game->InitiateSwitchScene(level);
					game->SwitchScene();
				}
				break;
			}
			case DIK_UP:
				if (currentStopPoint->isDirectionAllowed(1))
				{
					mario->SetState(OVERWORLD_MARIO_STATE_GO_UP);
					mario->SetCurrentStopPoint(NULL);
				}
				break;
			case DIK_LEFT:
				if (currentStopPoint->isDirectionAllowed(4))
				{
					mario->SetCurrentStopPoint(NULL);
					mario->SetState(OVERWORLD_MARIO_STATE_GO_LEFT);
				}
				break;
			case DIK_RIGHT:
				if (currentStopPoint->isDirectionAllowed(2))
				{
					mario->SetCurrentStopPoint(NULL);
					mario->SetState(OVERWORLD_MARIO_STATE_GO_RIGHT);
				}
				break;
			case DIK_DOWN:
				if (currentStopPoint->isDirectionAllowed(3))
				{
					mario->SetCurrentStopPoint(NULL);
					mario->SetState(OVERWORLD_MARIO_STATE_GO_DOWN);
				}
				break;
		}
	}
}
