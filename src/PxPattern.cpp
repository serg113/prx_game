#include "PxPattern.h"

#include <iostream>
#include <set>


std::set<PxPos> MatchThreeInDirectionXY::match(const std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position) const
{
	std::set<PxPos> matchPoints;

	auto points = matchThreeInSequenceDirectionXY(fieldMap, position);

	matchPoints.insert(points.begin(),points.end());

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




std::vector<PxPos> matchThreeInSequenceDirectionXY(const std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position)
{
	std::vector<PxPos> points1 = matchThreeInSequenceDirectionX(fieldPointMap, position);
	std::vector<PxPos> points2 = matchThreeInSequenceDirectionY(fieldPointMap, position);

	points1.insert(points1.end(), points2.begin(), points2.end());

	return points1;
}


std::vector<PxPos> matchThreeInSequenceDirectionX(const std::map<PxPos, PxFieldPoint>& fPointMap, PxPos position)
{
	auto x = position.X;
	auto y = position.Y;

	auto currentTxt = fPointMap.at(position).pawn->getTexture();

	if (fPointMap.find({ x - 1, y }) != fPointMap.end() && fPointMap.at({x - 1, y}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x - 2, y }) != fPointMap.end() && fPointMap.at({x - 2, y}).pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x - 1,y), PxPos(x - 2,y) };

		if (fPointMap.find({ x + 1, y }) != fPointMap.end() && fPointMap.at({x + 1, y}).pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x - 1,y), PxPos(x + 1,y) };
	}

	if (fPointMap.find({ x + 1, y }) != fPointMap.end() && fPointMap.at({x + 1, y}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x + 2, y }) != fPointMap.end() && fPointMap.at({x + 2, y}).pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x + 1,y), PxPos(x + 2,y) };
	}

	return {};
}

std::vector<PxPos> matchThreeInSequenceDirectionY(const std::map<PxPos, PxFieldPoint>& fPointMap, PxPos position)
{
	auto x = position.X;
	auto y = position.Y;

	auto currentTxt = fPointMap.at(position).pawn->getTexture();

	if (fPointMap.find({ x, y - 1 }) != fPointMap.end() && fPointMap.at({x, y - 1}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x, y - 2 }) != fPointMap.end() && fPointMap.at({x, y - 2}).pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x,y - 1), PxPos(x,y - 2) };

		if (fPointMap.find({ x, y + 1 }) != fPointMap.end() && fPointMap.at({x, y + 1}).pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x,y - 1), PxPos(x,y + 1) };
	}

	if (fPointMap.find({ x, y + 1 }) != fPointMap.end() && fPointMap.at({x, y + 1}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x, y + 2 }) != fPointMap.end() && fPointMap.at({x, y + 2}).pawn->getTexture() == currentTxt)
			return { PxPos(x,y), PxPos(x,y + 1), PxPos(x,y + 2) };
	}

	return {};
}

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints)
{
	std::cout << "deleteMatchingPoints(ponts = " << matchPoints.size() << " )" << std::endl;
	for (auto point : matchPoints)
		fieldPointMap[point].isPawnVisible = false;
}


void swapTextures(sf::Sprite* lhs, sf::Sprite* rhs)
{
	const sf::Texture* temp = lhs->getTexture();
	lhs->setTexture(*(rhs->getTexture()), true);
	rhs->setTexture(*temp, true);
}