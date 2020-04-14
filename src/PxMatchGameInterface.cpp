
#include "PxMatchGameInterface.h"
#include "PxMatchGameFacade.h"

InitializedEngine* initEngine(const Config& options)
{
	return (new PxMatchGameFacade())->setConfig(options)->initGameMap();
}