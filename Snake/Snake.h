#pragma once
#include "Actor.h"
#include "Updateable.h"
#include <vector>
#include "Vector.h"

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
