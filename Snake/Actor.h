#pragma once
#include "Screen.h"
#include "Drawable.h"

class Actor : public Drawable 
{
private:
	Screen& screen;
	int velocity[2] = { 0, 0 };
public:
	Actor(Screen& screen, int x, int y, char c) :
		screen(screen),
		Drawable(c, x, y) {};
	void OnUpdate() override;
	void SetVelocity(int x, int y);
	int* GetVelocity() const;
	Screen* GetScreen() const;
};
