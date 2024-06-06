#pragma once
#include"GreenKoopas.h"

#define KOOPAS_STATE_RUNNING 600
#define KOOPAS_RUNNING_SPEED 0.08f

class CIntroKoopas: public CGreenKoopas
{
protected:

public:
	CIntroKoopas(float x, float y, int level) :CGreenKoopas(x, y, level) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state, float nx=1);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};
