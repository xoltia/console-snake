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
	return x;
}

int Drawable::GetY() const
{
	return y;
}

void Drawable::Move(int xa, int ya)
{
	x += xa;
	y += ya;
	needsRedraw = true;
}

void Drawable::Move(int v[2])
{
	x += v[0];
	y += v[1];
	needsRedraw = true;
}

void Drawable::GoTo(int xa, int ya)
{
	x = xa;
	y = ya;
	needsRedraw = true;
}

void Drawable::GoTo(int v[2])
{
	x = v[0];
	y = v[1];
	needsRedraw = true;
}
