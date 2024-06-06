#include"IntroKoopas.h"

void CIntroKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	vx += ax * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CIntroKoopas::SetState(int state, float nx)
{
	if (state == KOOPAS_STATE_RUNNING)
	{
		this->state = KOOPAS_STATE_RUNNING;
		vx = KOOPAS_RUNNING_SPEED;
		ay = KOOPAS_GRAVITY;
	}
	CGreenKoopas::SetState(state, nx);
}
void CIntroKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny < 0)
	{
		vy = 0;
		if (state == GREENKOOPAS_STATE_JUMP)
			state = KOOPAS_STATE_WALKING;
		else if (state == KOOPAS_STATE_SHELL)
			vx = 0;
	}
	else if (e->ny > 0)
	{
		vy = 0;
	}
}