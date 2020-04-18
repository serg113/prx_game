#include "PxGame.h"
#include "PxMatchGame.h"


InitializedGame* createGame(const PxConfiguration options)
{
	return (new PxMatchGame(options))->init();
}
