#include "pch.h"
#include "Actor.h"

void Actor::SetVelocity(int x, int y)
{
	velocity[0] = x;
	velocity[1] = y;
}

int* Actor::GetVelocity() const
{
	return (int*)velocity;
}

void Actor::OnUpdate()
{
	if (screen.GetInput('W'))
		SetVelocity(0, -1);
	if (screen.GetInput('A'))
		SetVelocity(-1, 0);
	if (screen.GetInput('S'))
		SetVelocity(0, 1);
	if (screen.GetInput('D'))
		SetVelocity(1, 0);

	int futureX = GetX() + velocity[0];
	int futureY = GetY() + velocity[1];
	if ((futureX >= screen.GetWidth() || futureX < 0) || (futureY >= screen.GetHeight() || futureY < 0))
		return;
	Move(velocity);
}

Screen* Actor::GetScreen() const
{
	return &screen;
}