#pragma once

#include "Scene.h"

class CMenuKeyEventHandler : public CSceneKeyHandler
{
public:
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode){}
	virtual void KeyState(BYTE* states) {}
	CMenuKeyEventHandler(LPSCENE s) : CSceneKeyHandler(s) {};
};

