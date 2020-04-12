#include "PxEngine.h"
#include "PxEngineFacade.h"

#include <iostream>


PxEngineFacade::PxEngineFacade() 
{
	engine = new PxEngine();
}

PxEngineFacade* PxEngineFacade::setConfigs(Config params)
{
	dynamic_cast<PxEngine*>(engine)->setConfigs(params);

	return this;
}

PxEngineFacade* PxEngineFacade::initGameMap()
{
	dynamic_cast<PxEngine*>(engine)->initGameMap();

	return this;
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

PxEngineFacade* PxEngineFacade::draw(sf::RenderWindow* app)
{
	dynamic_cast<PxEngine*>(engine)->drawMap(app);

	return this;
}


PxEngineFacade* PxEngineFacade::swapPawns(PxPos firstPos, PxPos secondPos)
{
	dynamic_cast<PxEngine*>(engine)->swapPawns(firstPos, secondPos);

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

