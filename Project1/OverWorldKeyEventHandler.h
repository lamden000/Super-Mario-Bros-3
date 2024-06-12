
#pragma once

#include "Scene.h"

class COverWorldKeyEventHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states){}
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode){}
	COverWorldKeyEventHandler(LPSCENE s) : CSceneKeyHandler(s) {};
};


