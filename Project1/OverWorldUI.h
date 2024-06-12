#pragma once
#include "InGameUI.h"


class COverWorldUI : public CInGameUI {
public:
	COverWorldUI(float x, float y) { 
		this->x = x;
		this->y = y;
	};
	void Render();
};