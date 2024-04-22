#pragma once

#include "Scene.h"

class CKeyHandlerForLuigi : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CKeyHandlerForLuigi(LPSCENE s) :CSceneKeyHandler(s) {};
};


