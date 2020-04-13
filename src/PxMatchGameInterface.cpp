
#include "PxMatchGameInterface.h"
#include "PxMatchGameFacade.h"

UnInitializedEngine* getEngine() 
{
	return new PxMatchGameFacade();
}