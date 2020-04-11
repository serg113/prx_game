#pragma once

#include "PatternsBase.h"

void resetLastMovement(IResettableEngine* engine);

class PxEngineFacade
{
public:
	PxEngineFacade();
	PxEngineFacade* enableMovement(Movement2D dir);
	PxEngineFacade* draw(sf::RenderWindow* app);
	PxEngineFacade* setGameMap(std::map<PxPos, PxFieldPoint> fieldPointMap);
	PxEngineFacade* setMovement(PxPos start, PxPos end);
	PxEngineFacade* checkPattern(PatternCB_t pattern);
	PxEngineFacade* performMatchingAction(ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction = resetLastMovement);

private:
	PxEngineBase* engine;

};

