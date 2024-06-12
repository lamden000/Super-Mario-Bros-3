#include "MenuKeyEventHandler.h"

#include "Game.h"
#include "Intro.h"
#include "MenuUI.h"

#define OVERWORLD_ID 7

void CMenuKeyEventHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CIntro* intro= (CIntro*)game->GetCurrentScene();	
	if (!dynamic_cast<CMenuUI*>(intro->GetPlayer()))
		return;
	CMenuUI* ui= (CMenuUI*) intro->GetPlayer();
	switch (KeyCode)
	{
		case DIK_Q:
			ui->SetMode();
			break;
		case DIK_W:
			game->InitiateSwitchScene(OVERWORLD_ID);
			game->ResetGame();
			game->SwitchScene();
			break;
	}
}
