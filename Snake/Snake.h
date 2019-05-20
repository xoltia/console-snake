#pragma once
#include "Actor.h"
#include "Updateable.h"
#include <vector>

// TODO add vec2 coordinates elsewhere and have drawables, screen, etc be able to use it natively for working with positions

struct Vec2
{
	int x, y;
	Vec2(int x, int y) : x(x), y(y) {};
};

class Snake : public Updateable
{
private:
	char cellChar;
	Actor head;
	Drawable apple;
	std::vector<Vec2> positions;
	std::vector<Drawable*> cells;
public:
	Snake(char headChar, char cellChar, int startPos[2], Screen& screen, int cellCount);
	~Snake();

	void Draw();
	void OnUpdate() override;
	void Grow();
	void EatApple();
};
