#include "PxEngine.h"
#include "PxEngineFacade.h"

#include <iostream>


PxEngineFacade* PxEngineFacade::setMovement(PxPos firstPos, PxPos secondPos)
{
	dynamic_cast<PxEngine*>(engine)->setMovement(firstPos, secondPos);

	return this;
}

PxEngineFacade* PxEngineFacade::checkPattern(PatternCB_t pattern)
{
	dynamic_cast<PxEngine*>(engine)->checkPattern(pattern);
	
	return this;
}

PxEngineFacade* PxEngineFacade::performMatchingAction(ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction)
{
	dynamic_cast<PxEngine*>(engine)->performMatchingAction(matchingAction, failureAction);
	
	return this;
}


// free functions

void resetLastMovement(IResettableEngine* engine)
{
	std::cout << "[info] start of resetLastMovement" << std::endl;

	engine->resetMovement();

	std::cout << "[info] end of resetLastMovement" << std::endl;
}
