#pragma once

struct Vec2
{
	int x, y;
	Vec2() : x(0), y(0) {};
	Vec2(int x, int y) : x(x), y(y) {};
	Vec2(int v[2]) : x(v[0]), y(v[1]) {};
	
	Vec2 operator + (Vec2 const &vec);
	Vec2 operator += (Vec2 const &vec);
	Vec2 operator - (Vec2 const &vec);
	Vec2 operator -= (Vec2 const &vec);
	bool operator == (Vec2 const &vec);
	bool operator != (Vec2 const &vec);
};
