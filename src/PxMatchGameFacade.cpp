#include "PxEngine.h"
#include "PxMatchGameFacade.h"

#include <iostream>


PxMatchGameFacade::PxMatchGameFacade()
{
	engine = new PxEngine();
}

UnInitializedEngine* PxMatchGameFacade::setConfigs(Config params)
{
	dynamic_cast<PxEngine*>(engine)->setConfigs(params);

	return this;
}

UnInitializedEngine* PxMatchGameFacade::addPatternToMatch(PxPattern* pattern)
{
	dynamic_cast<PxEngine*>(engine)->addPatternToMatch(pattern);

	return this;
}

InitializedEngine* PxMatchGameFacade::initGameMap()
{
	dynamic_cast<PxEngine*>(engine)->initGameMap();

	return this;
}

InitializedEngine* PxMatchGameFacade::setDifferedBackground(PxPos position, sf::Texture* txt)
{
	dynamic_cast<PxEngine*>(engine)->setDifferedBackground(position, txt);

	return this;
}

InitializedEngine* PxMatchGameFacade::resetDifferedBackground(PxPos position)
{
	dynamic_cast<PxEngine*>(engine)->resetDifferedBackground(position);

	return this;
}

InitializedEngine* PxMatchGameFacade::draw(sf::RenderWindow* app)
{
	dynamic_cast<PxEngine*>(engine)->drawMap(app);

	return this;
}


InitializedEngine* PxMatchGameFacade::swapPawnsAndMatch(PxPos firstPos, PxPos secondPos)
{
	dynamic_cast<PxEngine*>(engine)->swapPawns(firstPos, secondPos);
	dynamic_cast<PxEngine*>(engine)->matchAllPatterns();

	return this;
}



