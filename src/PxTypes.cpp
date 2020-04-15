#include "PxTypes.h"


PxField::PxField(sf::Sprite* back, sf::Sprite* front) : bgTile(back), pawn(front) {};

PxPoint::PxPoint() :X(0), Y(0) {};
PxPoint::PxPoint(size_t x, size_t y) :X(x), Y(y) {};

bool operator<(const PxPoint& lhs, const PxPoint& rhs)
{
	return (lhs.X * 100 + lhs.Y) < (rhs.X * 100 + rhs.Y);
}