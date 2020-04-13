#include "PxEngine.h"
#include "PxEngineFacade.h"

#include <iostream>


PxEngineFacade::PxEngineFacade() 
{
	engine = new PxEngine();
}

UnInitializedEngine* PxEngineFacade::setConfigs(Config params)
{
	dynamic_cast<PxEngine*>(engine)->setConfigs(params);

	return this;
}

UnInitializedEngine* PxEngineFacade::addPatternToMatch(PxPatternBase* pattern)
{
	dynamic_cast<PxEngine*>(engine)->addPatternToMatch(pattern);

	return this;
}

InitializedEngine* PxEngineFacade::initGameMap()
{
	dynamic_cast<PxEngine*>(engine)->initGameMap();

	return this;
}

InitializedEngine* PxEngineFacade::setDifferedBackground(PxPos position, sf::Texture* txt)
{
	dynamic_cast<PxEngine*>(engine)->setDifferedBackground(position, txt);

	return this;
}

InitializedEngine* PxEngineFacade::resetDifferedBackground(PxPos position)
{
	dynamic_cast<PxEngine*>(engine)->resetDifferedBackground(position);

	return this;
}

InitializedEngine* PxEngineFacade::draw(sf::RenderWindow* app)
{
	dynamic_cast<PxEngine*>(engine)->drawMap(app);

	return this;
}


InitializedEngine* PxEngineFacade::swapPawnsAndMatch(PxPos firstPos, PxPos secondPos)
{
	dynamic_cast<PxEngine*>(engine)->swapPawns(firstPos, secondPos);
	dynamic_cast<PxEngine*>(engine)->matchAllPatterns();

	return this;
}



