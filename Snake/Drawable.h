#pragma once

#include "Updateable.h"

class Drawable : public Updateable
{
private:
	int x, y;
	bool needsRedraw;
public:
	char Character;

	void Move(int xa, int ya);
	void Move(int v[2]);

	void GoTo(int xa, int ya);
	void GoTo(int v[2]);

	Drawable(int x, int y) : Character('*'), x(x), y(y) {};
	Drawable(char Char, int x, int y) : Character(Char), x(x), y(y) {};

	int GetX() const;
	int GetY() const;
	bool NeedsRedraw();
	void ClearRedraw();
};
