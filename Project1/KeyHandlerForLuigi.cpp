#include "KeyHandlerForLuigi.h"

#include "debug.h"
#include "Game.h"

#include "Luigi.h"
#include "PlayScene.h"

#define INTRO_ID 6

void CKeyHandlerForLuigi::OnKeyDown(int KeyCode)
{
	CLuigi* luigi = (CLuigi*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_DOWN:
		luigi->SetState(LUIGI_STATE_SIT);
	case DIK_S:
		luigi->SetState(LUIGI_STATE_JUMP);
		break;
	case DIK_1:
		luigi->SetLevel(LUIGI_LEVEL_SMALL);
		break;
	case DIK_2:
		luigi->SetLevel(LUIGI_LEVEL_BIG);
		break;
	case DIK_0:
		luigi->SetState(LUIGI_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CKeyHandlerForLuigi::OnKeyUp(int KeyCode)
{
	CLuigi* luigi = (CLuigi*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		luigi->SetState(LUIGI_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		luigi->SetState(LUIGI_STATE_SIT_RELEASE);
		break;
	}
}

void CKeyHandlerForLuigi::KeyState(BYTE* states)
{
	CLuigi* luigi = (CLuigi*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			luigi->SetState(LUIGI_STATE_RUNNING_RIGHT);
		else
			luigi->SetState(LUIGI_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			luigi->SetState(LUIGI_STATE_RUNNING_LEFT);
		else
			luigi->SetState(LUIGI_STATE_WALKING_LEFT);
	}
	else
		luigi->SetState(LUIGI_STATE_IDLE);
}