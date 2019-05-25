#include "pch.h"
#include <iostream>
#include <string>
#include "Screen.h"

bool Screen::keys[128] = { false };
std::vector<const char*> Screen::messages;

bool Screen::Destroy(Drawable* drawable)
{
	for (int i = 0; i < drawables.size(); i++)
	{
		if (drawables[i] == drawable)
		{
			drawables.erase(drawables.begin() + i);
			return true;
		}
	}
	return false;
}

void Screen::Add(Drawable* drawable)
{
	drawables.push_back(drawable);
}

void Screen::Add(Updateable* updateable)
{
	updateables.push_back(updateable);
}

Drawable* Screen::DrawableAt(int x, int y)
{
	for (int i = 0; i < drawables.size(); i++)
		if (drawables[i]->GetX() == x && drawables[i]->GetY() == y) return drawables[i];
	return nullptr;
}

Drawable* Screen::DrawableAt(Vec2 pos)
{
	for (int i = 0; i < drawables.size(); i++)
		if (drawables[i]->GetPosition() == pos) return drawables[i];
	return nullptr;
}

bool Screen::ShouldRedraw()
{
	for (int i = 0; i < drawables.size(); i++)
		if (drawables[i]->NeedsRedraw()) return true;
	return false;
}

void Screen::Update()
{
	for (int i = 0; i < drawables.size(); i++)
	{
		drawables[i]->ClearRedraw();
		drawables[i]->OnUpdate();
	}

	for (int i = 0; i < updateables.size(); i++)
	{
		updateables[i]->OnUpdate();
	}

	for (int i = 0; i < 128; i++)
	{
		keys[i] = false;
	}
}

void Screen::Render()
{
	system("cls");
	std::string scoreStr = std::string("Score: ") + std::to_string(score);
	std::string padding = std::string(width - scoreStr.length() + 1, ' ');
	std::cout << padding << scoreStr << padding << std::endl;
	std::string horizontalBorder = '+' + std::string(width*2, '-') + "+\n";
	std::cout << horizontalBorder;
	
	for (int y = 0; y < height; y++)
	{
		std::string row = "|";
		for (int x = 0; x < width; x++)
		{
			row += " ";
			Drawable* drawableAtPos = DrawableAt(x, y);
			if (drawableAtPos)
				row += drawableAtPos->Character;
			else
				row += " ";
		}
		row += "|";
		std::cout << row << std::endl;
	}

	std::cout << horizontalBorder;
	for (int i = 0; i < messages.size(); i++)
	{
		std::cout << messages[i] << std::endl;
	}
}

LRESULT CALLBACK Screen::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;

	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
		int keyCode = kbdStruct.vkCode;
		if (keyCode >= 0 && keyCode <= 127)
		{
			switch (wParam)
			{
			case WM_KEYDOWN:
				keys[keyCode] = true;
				break;
			/*case WM_KEYUP:
				keys[keyCode] = false;
				break;*/
			}
		}
	}
	return (fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

bool Screen::GetInput(char key)
{
	int code = (int)key;
	if (code < 0 || code > 127)
		return false;
	return keys[code];
}

void Screen::Log(const char* message)
{
	messages.push_back(message);
}

void Screen::ClearLog()
{
	messages.clear();
}

int Screen::GetHeight() const
{
	return height;
}

int Screen::GetWidth() const
{
	return width;
}

std::vector<Drawable*> Screen::GetDrawables() const
{
	return drawables;
}

void Screen::IncrementScore(int amount)
{
	score += amount;
}

int Screen::GetScore() const
{
	return score;
}
