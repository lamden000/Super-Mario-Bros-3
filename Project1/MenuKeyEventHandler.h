#pragma once

#include "Scene.h"

class CMenuKeyEventHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CMenuKeyEventHandler(LPSCENE s) : CSceneKeyHandler(s) {};
};

