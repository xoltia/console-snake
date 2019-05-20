#include "pch.h"
#include "Snake.h"
#include "Log.h"
#include <iostream>
#include <stdlib.h>

Snake::Snake(char headChar, char cellChar, int startPos[2], Screen& screen, int cellCount)
	: head(screen, startPos[0], startPos[1], headChar), cellChar(cellChar), apple(5, 5)
{
	head.SetVelocity(1, 0);
	positions.insert(positions.begin(), Vec2(head.GetX(), head.GetY()));
	for (int i = 0; i < cellCount; i++)
	{
		cells.push_back(new Drawable(cellChar, startPos[0], startPos[1]));
		positions.push_back(Vec2(startPos[0], startPos[1]));
	}
	head.GetScreen()->Add(&apple);
}

Snake::~Snake()
{
	for (int i = 0; i < cells.size(); i++)
	{
		delete cells[i];
	}
	cells.clear();
}

void Snake::Draw()
{
	Screen* gameScreen = head.GetScreen();
	gameScreen->Add(&head);
	for (int i = 0; i < cells.size(); i++)
	{
		gameScreen->Add(cells[i]);
	}
}

void Snake::OnUpdate()
{
	positions.insert(positions.begin(), Vec2(head.GetX(), head.GetY()));
	for (int i = 0; i < cells.size(); i++)
	{
		Vec2 newPos = positions[i+1];
		cells[i]->GoTo(newPos.x, newPos.y);
		if (newPos.x == head.GetX() && newPos.y == head.GetY())
		{
			head.GetScreen()->shouldClose = true;
		}
	}
	positions.erase(positions.end() - 1);

	if (head.GetX() == apple.GetX() && head.GetY() == apple.GetY())
		EatApple();
}

void Snake::EatApple()
{
	Grow();
	head.GetScreen()->IncrementScore(1);
	Vec2 applePos = Vec2(rand() % head.GetScreen()->GetWidth(), rand() % head.GetScreen()->GetHeight());
	while (head.GetScreen()->DrawableAt(applePos.x, applePos.y))
	{
		applePos = Vec2(rand() % head.GetScreen()->GetWidth(), rand() % head.GetScreen()->GetHeight());
	}
	apple.GoTo(applePos.x, applePos.y);
}

void Snake::Grow()
{
	int* hVel = head.GetVelocity();
	Vec2 last = positions.at(positions.size() - 1);
	Vec2 newCellPos = Vec2(last.x - hVel[0], last.y - hVel[1]);
	Drawable* newCell = new Drawable(cellChar, newCellPos.x, newCellPos.y);
	positions.push_back(newCellPos);
	cells.push_back(newCell);
	head.GetScreen()->Add(newCell);
}