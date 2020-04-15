#include "PxPatterns.h"

#include <iostream>
#include <set>


std::set<PxPoint> MatchThreeInDirectionXY::match(const std::map<PxPoint, PxField>& fieldMap, PxPoint position) const
{
	std::set<PxPoint> matchPoints;

	auto points = matchThreeInSequenceDirectionXY(fieldMap, position);

	matchPoints.insert(points.begin(),points.end());

	return matchPoints;
}

void MatchThreeInDirectionXY::actOnSuccess(std::map<PxPoint, PxField>& fieldMap, std::set<PxPoint>& points) const
{
	deleteMatchingPoints(fieldMap, { points.begin(), points.end() });
}

void MatchThreeInDirectionXY::actOnFailure(std::map<PxPoint, PxField>& fieldMap, PxPoint position1, PxPoint position2) const
{
	swapTextures(fieldMap[position1].pawn, fieldMap[position2].pawn);
}




std::vector<PxPoint> matchThreeInSequenceDirectionXY(const std::map<PxPoint, PxField>& fieldPointMap, PxPoint position)
{
	std::vector<PxPoint> points1 = matchThreeInSequenceDirectionX(fieldPointMap, position);
	std::vector<PxPoint> points2 = matchThreeInSequenceDirectionY(fieldPointMap, position);

	points1.insert(points1.end(), points2.begin(), points2.end());

	return points1;
}


std::vector<PxPoint> matchThreeInSequenceDirectionX(const std::map<PxPoint, PxField>& fPointMap, PxPoint position)
{
	auto x = position.X;
	auto y = position.Y;

	auto currentTxt = fPointMap.at(position).pawn->getTexture();

	if (fPointMap.find({ x - 1, y }) != fPointMap.end() && fPointMap.at({x - 1, y}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x - 2, y }) != fPointMap.end() && fPointMap.at({x - 2, y}).pawn->getTexture() == currentTxt)
			return { PxPoint(x,y), PxPoint(x - 1,y), PxPoint(x - 2,y) };

		if (fPointMap.find({ x + 1, y }) != fPointMap.end() && fPointMap.at({x + 1, y}).pawn->getTexture() == currentTxt)
			return { PxPoint(x,y), PxPoint(x - 1,y), PxPoint(x + 1,y) };
	}

	if (fPointMap.find({ x + 1, y }) != fPointMap.end() && fPointMap.at({x + 1, y}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x + 2, y }) != fPointMap.end() && fPointMap.at({x + 2, y}).pawn->getTexture() == currentTxt)
			return { PxPoint(x,y), PxPoint(x + 1,y), PxPoint(x + 2,y) };
	}

	return {};
}

std::vector<PxPoint> matchThreeInSequenceDirectionY(const std::map<PxPoint, PxField>& fPointMap, PxPoint position)
{
	auto x = position.X;
	auto y = position.Y;

	auto currentTxt = fPointMap.at(position).pawn->getTexture();

	if (fPointMap.find({ x, y - 1 }) != fPointMap.end() && fPointMap.at({x, y - 1}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x, y - 2 }) != fPointMap.end() && fPointMap.at({x, y - 2}).pawn->getTexture() == currentTxt)
			return { PxPoint(x,y), PxPoint(x,y - 1), PxPoint(x,y - 2) };

		if (fPointMap.find({ x, y + 1 }) != fPointMap.end() && fPointMap.at({x, y + 1}).pawn->getTexture() == currentTxt)
			return { PxPoint(x,y), PxPoint(x,y - 1), PxPoint(x,y + 1) };
	}

	if (fPointMap.find({ x, y + 1 }) != fPointMap.end() && fPointMap.at({x, y + 1}).pawn->getTexture() == currentTxt)
	{
		if (fPointMap.find({ x, y + 2 }) != fPointMap.end() && fPointMap.at({x, y + 2}).pawn->getTexture() == currentTxt)
			return { PxPoint(x,y), PxPoint(x,y + 1), PxPoint(x,y + 2) };
	}

	return {};
}

void deleteMatchingPoints(std::map<PxPoint, PxField>& fieldPointMap, std::vector<PxPoint> matchPoints)
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