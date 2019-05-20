#include "pch.h"
#include "Drawable.h"
#include <vector>

bool Drawable::NeedsRedraw()
{
	return needsRedraw;
}

void Drawable::ClearRedraw()
{
	needsRedraw = false;
}

int Drawable::GetX() const
{
	return position.x;
}

int Drawable::GetY() const
{
	return position.y;
}

Vec2 Drawable::GetPosition() const
{
	return position;
}

void Drawable::Move(int xa, int ya)
{
	position.x += xa;
	position.y += ya;
	needsRedraw = true;
}

void Drawable::Move(int v[2])
{
	position.x += v[0];
	position.y += v[1];
	needsRedraw = true;
}

void Drawable::Move(Vec2 v)
{
	position += v;
	needsRedraw = true;
}

void Drawable::GoTo(int xa, int ya)
{
	position.x = xa;
	position.y = ya;
	needsRedraw = true;
}

void Drawable::GoTo(int v[2])
{
	position.x = v[0];
	position.y = v[1];
	needsRedraw = true;
}

void Drawable::GoTo(Vec2 v)
{
	position = v;
	needsRedraw = true;
}
