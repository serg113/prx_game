#pragma once

#include "PatternsBase.h"

#include <vector>
#include <map>


class PxEngineFacade
{
public:
	PxEngineFacade* setMovement(PxPos start, PxPos end);
	PxEngineFacade* checkPattern(PatternCB_t pattern);
	PxEngineFacade* performMatchingAction(ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction = resetLastMovement);

private:
	PxEngineBase* engine;

};

void resetLastMovement(IResettableEngine* engine);