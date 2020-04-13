
#include "PxEngineBase.h"
#include "PxEngineFacade.h"

UnInitializedEngine* getEngine() 
{
	return new PxEngineFacade();
}