#include "MenuKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "PlayScene.h"

#define INTRO_ID 6

void CMenuKeyEventHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	}
}

void CMenuKeyEventHandler::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	}
}

void CMenuKeyEventHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT))
	{
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
	}
}