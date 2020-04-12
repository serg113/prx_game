#include "PatternsBase.h"

#include <iostream>

PxFieldPoint::PxFieldPoint(sf::Sprite* back, sf::Sprite* front) : bgTile(back), pawn(front) {};

PxPos::PxPos() :X(0), Y(0) {};
PxPos::PxPos(size_t x, size_t y) :X(x), Y(y) {};

bool operator<(const PxPos& lhs, const PxPos& rhs)
{
	return (lhs.X * 100 + lhs.Y) < (rhs.X * 100 + rhs.Y);
}

std::vector<PxPos> matchThreeInSequenceDirectionX(std::map<PxPos, PxFieldPoint>& fPointMap, PxPos position)
{
	std::cout << "matchThreeInSequenceDirectionX()" << std::endl;

	auto x = position.X;
	auto y = position.Y;

	auto currentTxt = fPointMap[position].pawn->getTexture();

	if (fPointMap.find({ x - 1, y }) != fPointMap.end() && fPointMap[{x - 1, y}].pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x - 2, y }) != fPointMap.end() && fPointMap[{x - 2, y}].pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x - 1,y), PxPos(x - 2,y) };

		if (fPointMap.find({ x + 1, y }) != fPointMap.end() && fPointMap[{x + 1, y}].pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x - 1,y), PxPos(x + 1,y) };
	}

	if (fPointMap.find({ x + 1, y }) != fPointMap.end() && fPointMap[{x + 1, y}].pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x + 2, y }) != fPointMap.end() && fPointMap[{x + 2, y}].pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x + 1,y), PxPos(x + 2,y) };
	}

	return {};
}

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints)
{
	std::cout << "deleteMatchingPoints(ponts = " << matchPoints.size() << " )" << std::endl;
	for (auto point : matchPoints)
		fieldPointMap[point].pawn = nullptr;
}