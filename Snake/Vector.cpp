#include "pch.h"
#include "Vector.h"

Vec2 Vec2::operator+(Vec2 const &vec)
{
	Vec2 result;
	result.x = x + vec.x;
	result.y = y + vec.y;
	return result;
}

Vec2 Vec2::operator += (Vec2 const &vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vec2 Vec2::operator - (Vec2 const &vec)
{
	Vec2 result;
	result.x = x - vec.x;
	result.y = y - vec.y;
	return result;
}
Vec2 Vec2::operator -= (Vec2 const &vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

bool Vec2::operator == (Vec2 const &vec)
{
	return (x == vec.x && vec.y == y);
}

bool Vec2::operator != (Vec2 const &vec)
{
	return !(*(this) == vec);
}
