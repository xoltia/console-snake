#pragma once

#include "Updateable.h"
#include "Vector.h"

class Drawable : public Updateable
{
private:
	Vec2 position;
	bool needsRedraw;
public:
	char Character;

	void Move(int xa, int ya);
	void Move(int v[2]);
	void Move(Vec2 v);

	void GoTo(int xa, int ya);
	void GoTo(int v[2]);
	void GoTo(Vec2 v);

	Drawable(int x, int y) : Character('*'), position(x, y) {};
	Drawable(Vec2 pos) : Character('*'), position(pos) {};
	Drawable(char Char, Vec2 pos) : Character(Char), position(pos) {};
	Drawable(char Char, int x, int y) : Character(Char), position(x, y) {};

	int GetX() const;
	int GetY() const;
	Vec2 GetPosition() const;
	bool NeedsRedraw();
	void ClearRedraw();
};
