#include "PxEngine.h"

#include <exception>


PxEngine* PxEngine::setMovement(PxPos start, PxPos end)
{
	exchEnd = end;

	exchStart = start;

	std::swap(fieldPointMap[start].pawn, fieldPointMap[end].pawn);

	return this;
}

PxEngine* PxEngine::checkPattern(Pattern_t pattern)
{
	for (auto exPoint : { exchStart, exchEnd })
		for (auto matchPoint : pattern(fieldPointMap, fieldPointMap[exPoint]))
			matchPoints.push_back(matchPoint);

	return this;
}

PxEngine* PxEngine::performMatchingAction(ActOnSuccess_t matchingAction, ActOnFail_t failureAction)
{
	if (matchPoints.empty())
		failureAction(this);
	else
		matchingAction(this, fieldPoints);
}

std::vector<PxFieldPoint> PxEngine::getPatternMatchPoints(Pattern_t pattern) const
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
	std::swap(fieldPointMap[this->exchStart].pawn, fieldPointMap[this->exchStart].pawn);
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

void resetLastMovement(IResettableEngine* engine)
{
	engine->resetMovement();
}


void PxDraw(PxEngine* engine, sf::RenderWindow* app)
{
	auto fPoints = engine->getFieldPoints();

	for (auto point : fPoints)
	{
		app->draw(*(point.bgTile));
		app->draw(*(point.pawn));
	}

};