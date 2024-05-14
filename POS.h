#pragma once
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

class POS
{
public:
	int x;
	int y;
	int XYDir(const POS& other)const
	{
		if (x == other.x && y == other.y - 1) { return UP; }
		else if (x == other.x && y == other.y + 1) { return DOWN; }
		else if (x == other.x - 1 && y == other.y) { return LEFT; }
		else if (x == other.x + 1 && y == other.y) { return RIGHT; }
	}
	bool operator == (const POS& other)const
	{
		return x == other.x && y == other.y;
	}
	bool operator != (const POS& other)const
	{
		return x != other.x || y != other.y;
	}
	POS operator -(const POS& other)const
	{
		POS result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}
	
	POS operator +(const POS& other)const
	{
		POS result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}
	POS() : x(0), y(0) {}
	POS(int sx, int sy) : x(sx), y(sy) {}
	POS(const POS& p) { x = p.x; y = p.y; }
};

