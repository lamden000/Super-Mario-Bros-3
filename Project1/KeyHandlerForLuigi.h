#pragma once

#include "KeyEventHandlerForMario.h"

class CKeyHandlerForLuigi : public CSampleKeyHandler
{
public:
	void KeyState(BYTE* states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	CKeyHandlerForLuigi(LPSCENE s) :CSampleKeyHandler(s) {};
};


