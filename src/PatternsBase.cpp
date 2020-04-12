#include "PatternsBase.h"
#include "ConfigParser.h"
#include <iostream>
#include <set>

PxFieldPoint::PxFieldPoint(sf::Sprite* back, sf::Sprite* front) : bgTile(back), pawn(front) {};

PxPos::PxPos() :X(0), Y(0) {};
PxPos::PxPos(size_t x, size_t y) :X(x), Y(y) {};

bool operator<(const PxPos& lhs, const PxPos& rhs)
{
	return (lhs.X * 100 + lhs.Y) < (rhs.X * 100 + rhs.Y);
}

void swapTextures(sf::Sprite* lhs, sf::Sprite* rhs)
{
	const sf::Texture* temp = lhs->getTexture();
	lhs->setTexture(*(rhs->getTexture()), true);
	rhs->setTexture(*temp, true);
}

// pattern base
std::set<PxPos> MatchThreeInDirectionXY::match(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const
{
	std::set<PxPos> matchPoints;

	auto points1 = matchThreeInSequenceDirectionXY(fieldMap, position1);
	auto points2 = matchThreeInSequenceDirectionXY(fieldMap, position2);

	matchPoints.insert(points1.begin(),points1.end());
	matchPoints.insert(points2.begin(), points2.end());

	return matchPoints;
}

void MatchThreeInDirectionXY::actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const
{
	deleteMatchingPoints(fieldMap, { points.begin(), points.end() });
}

void MatchThreeInDirectionXY::actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const
{
	swapTextures(fieldMap[position1].pawn, fieldMap[position2].pawn);
}


//end of pattern base

std::vector<PxPos> matchThreeInSequenceDirectionXY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position)
{
	std::vector<PxPos> points1 = matchThreeInSequenceDirectionX(fieldPointMap, position);
	std::vector<PxPos> points2 = matchThreeInSequenceDirectionY(fieldPointMap, position);

	points1.insert(points1.end(), points2.begin(), points2.end());

	return points1;
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

std::vector<PxPos> matchThreeInSequenceDirectionY(std::map<PxPos, PxFieldPoint>& fPointMap, PxPos position)
{
	std::cout << "matchThreeInSequenceDirectionY()" << std::endl;

	auto x = position.X;
	auto y = position.Y;

	auto currentTxt = fPointMap[position].pawn->getTexture();

	if (fPointMap.find({ x, y - 1 }) != fPointMap.end() && fPointMap[{x, y - 1}].pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x, y - 2 }) != fPointMap.end() && fPointMap[{x, y - 2}].pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x,y - 1), PxPos(x,y - 2) };

		if (fPointMap.find({ x, y + 1 }) != fPointMap.end() && fPointMap[{x, y + 1}].pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x,y - 1), PxPos(x,y + 1) };
	}

	if (fPointMap.find({ x, y + 1 }) != fPointMap.end() && fPointMap[{x, y + 1}].pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x, y + 2 }) != fPointMap.end() && fPointMap[{x, y + 2}].pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x,y + 1), PxPos(x,y + 2) };
	}

	return {};
}

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints)
{
	std::cout << "deleteMatchingPoints(ponts = " << matchPoints.size() << " )" << std::endl;
	for (auto point : matchPoints)
		fieldPointMap[point].pawn->setTexture(*(fieldPointMap[point].bgTile->getTexture()),true);
}
