#include "PxEngine.h"

#include <exception>
#include <iostream>

void PxEngine::setMovement(PxPos start, PxPos end)
{
	secondPos = end;

	firstPos = start;

	std::swap(fieldPointMap[start].pawn, fieldPointMap[end].pawn);
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
		matchingAction(this, fieldPoints);

}


std::vector<PxFieldPoint> PxEngine::getPatternMatchPoints(PatternCB_t pattern) const
{
	return this->matchPoints;
}

std::vector<PxFieldPoint> PxEngine::getFieldPoints() const
{
	return this->fieldPoints;
}

std::map<PxPos, PxFieldPoint> PxEngine::getFieldPointMap() const
{
	return this->getFieldPointMap;
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


// free functions

void PxDraw(PxEngine* engine, sf::RenderWindow* app)
{
	auto fPoints = engine->getFieldPoints();

	for (auto point : fPoints)
	{
		app->draw(*(point.bgTile));
		app->draw(*(point.pawn));
	}

};