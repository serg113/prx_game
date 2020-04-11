#include "PxEngine.h"

#include <exception>
#include <iostream>
#include <cmath>



PxEngine::PxEngine() {};

void PxEngine::enableMovementDirections(Movement2D dir)
{
	switch (dir)
	{
	case Movement2D::DX: move2d.isDxEnabled = true;
	case Movement2D::DY: move2d.isDyEnabled = true;
	case Movement2D::DXY: move2d.isDxyEnabled = true;
	}
}

void PxEngine::setFieldPointMap(const std::map<PxPos, PxFieldPoint>  fPoints)
{
	fieldPointMap = fPoints;
}

void PxEngine::setMovement(const PxPos p1, const PxPos p2)
{
	if (!isMovementPossible(p1, p2))
		return;

	firstPos = p1;
	secondPos = p2;

	swapTextures(fieldPointMap[p1].pawn, fieldPointMap[p2].pawn);
}

void PxEngine::swapTextures(sf::Sprite* lhs, sf::Sprite* rhs)
{
	const sf::Texture* temp = lhs->getTexture();
	lhs->setTexture(*(rhs->getTexture()), true);
	rhs->setTexture(*temp, true);
}

void PxEngine::checkPattern(PatternCB_t pattern)
{
	for (auto exPoint : { firstPos, secondPos })
		for (auto matchPoint : pattern(fieldPointMap, fieldPointMap[exPoint]))
			matchPoints.push_back(matchPoint);
}

void PxEngine::performMatchingAction(ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction)
{
	if (matchPoints.empty())
		failureAction(this);
	else
		matchingAction(this);
}


std::vector<PxFieldPoint> PxEngine::getPatternMatchPoints(PatternCB_t pattern) const
{
	return this->matchPoints;
}

std::map<PxPos, PxFieldPoint> PxEngine::getFieldPointMap() const
{
	return this->fieldPointMap;
}

void PxEngine::resetMovement()
{
	std::swap(fieldPointMap[this->firstPos].pawn, fieldPointMap[this->secondPos].pawn);
}

void PxEngine::matchThreeInSequenceDirectionX()
{ 
	throw std::exception("[not implemented] matchThreeInSequenceDirectionX()");
}

void PxEngine::matchThreeInSequenceDirectoryY()
{
	throw std::exception("[not implemented] matchThreeInSequenceDirectionY()");
}

void PxEngine::matchFourInSquare()
{
	throw std::exception("[not implemented] matchFourInSquare()");
}

void PxEngine::matchTypeT()
{
	throw std::exception("[not implemented] matchTypeT()");
}

void PxEngine::drawMap(sf::RenderWindow* app)
{
	for (auto point : fieldPointMap)
	{
		app->draw(*(point.second.bgTile));
		app->draw(*(point.second.pawn));
	}
};

bool PxEngine::isMovementPossible(const PxPos p1, const PxPos p2)
{
	if ((p1.X < 0 || p2.X < 0) || (p1.Y < 0 || p2.Y < 0))
		return false;

	if ((abs((int)(p1.X - p2.X)) + abs((int)(p1.Y - p2.Y))) == 1)
		return true;

	return false;
}