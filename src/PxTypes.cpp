#include "PxTypes.h"


PxFieldPoint::PxFieldPoint(sf::Sprite* back, sf::Sprite* front) : bgTile(back), pawn(front) {};

PxPos::PxPos() :X(0), Y(0) {};
PxPos::PxPos(size_t x, size_t y) :X(x), Y(y) {};

bool operator<(const PxPos& lhs, const PxPos& rhs)
{
	return (lhs.X * 100 + lhs.Y) < (rhs.X * 100 + rhs.Y);
}