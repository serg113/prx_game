#include "PxEngine.h"
#include "PxEngineFacade.h"

#include <iostream>


PxEngineFacade::PxEngineFacade() 
{
	engine = new PxEngine();
}

PxEngineFacade* PxEngineFacade::setDifferedBackground(PxPos position, sf::Texture* txt)
{
	dynamic_cast<PxEngine*>(engine)->setDifferedBackground(position, txt);

	return this;
}

PxEngineFacade* PxEngineFacade::resetDifferedBackground(PxPos position)
{
	dynamic_cast<PxEngine*>(engine)->resetDifferedBackground(position);

	return this;
}

PxEngineFacade* PxEngineFacade::enableMovement(Movement2D dir)
{
	dynamic_cast<PxEngine*>(engine)->enableMovementDirections(dir);

	return this;
}

PxEngineFacade* PxEngineFacade::draw(sf::RenderWindow* app)
{
	dynamic_cast<PxEngine*>(engine)->drawMap(app);

	return this;
}

PxEngineFacade* PxEngineFacade::setGameMap(std::map<PxPos, PxFieldPoint> fieldPointMap)
{
	dynamic_cast<PxEngine*>(engine)->setFieldPointMap(fieldPointMap);

	return this;
}

PxEngineFacade* PxEngineFacade::setMovement(PxPos firstPos, PxPos secondPos)
{
	dynamic_cast<PxEngine*>(engine)->setMovement(firstPos, secondPos);

	return this;
}

PxEngineFacade* PxEngineFacade::checkPatterns()
{
	dynamic_cast<PxEngine*>(engine)->checkPatterns();
	
	return this;
}


PxEngineFacade* PxEngineFacade::addPatternToMatch(PatternCB_t pattern, ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction)
{
	dynamic_cast<PxEngine*>(engine)->addPatternToMatch(pattern, matchingAction, failureAction);

	return this;
}

PxEngineFacade* PxEngineFacade::addPatternToMatch(PxPatternBase* pattern)
{
	dynamic_cast<PxEngine*>(engine)->addPatternToMatch(pattern);

	return this;
}

PxEngineFacade* PxEngineFacade::matchAllPatterns()
{
	dynamic_cast<PxEngine*>(engine)->matchAllPatterns();

	return this;
}

