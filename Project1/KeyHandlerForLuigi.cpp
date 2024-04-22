#include "KeyHandlerForLuigi.h"

#include "debug.h"
#include "Game.h"

#include "Luigi.h"
#include "PlayScene.h"

void CKeyHandlerForLuigi::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CLuigi* luigi = (CLuigi*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		luigi->SetState(LUIGI_STATE_SIT);
		break;
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
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CLuigi* luigi = (CLuigi*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
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
	LPGAME game = CGame::GetInstance();
	CLuigi* luigi = (CLuigi*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (luigi == nullptr)
		return;

	if (luigi->GetAutoRunning())
	{
		if (luigi->GetMoveDirection() == D3DXVECTOR2(1.0f, 0.0f))
		{
			if (game->IsKeyDown(DIK_A))
				luigi->SetState(LUIGI_STATE_RUNNING_RIGHT);
			else
				luigi->SetState(LUIGI_STATE_WALKING_RIGHT);
		}
		else if (luigi->GetMoveDirection() == D3DXVECTOR2(-1.0f, 0.0f))
		{
			if (game->IsKeyDown(DIK_A))
				luigi->SetState(LUIGI_STATE_RUNNING_LEFT);
			else
				luigi->SetState(LUIGI_STATE_WALKING_LEFT);
		}
	}

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