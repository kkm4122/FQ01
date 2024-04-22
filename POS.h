#pragma once
class POS
{
public:
	int x;
	int y;

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

