#include "PxMatchGameFacade.h"
#include "PxEngine.h"


PxMatchGameFacade::PxMatchGameFacade()
{
	engine = new PxEngine();
}

UnInitializedEngine* PxMatchGameFacade::setConfigs(Config params)
{
	engine->setConfigs(params);

	return this;
}

UnInitializedEngine* PxMatchGameFacade::addPatternToMatch(PxPattern* pattern)
{
	engine->addPatternToMatch(pattern);

	return this;
}

InitializedEngine* PxMatchGameFacade::initGameMap()
{
	engine->initGameMap();

	return this;
}

InitializedEngine* PxMatchGameFacade::setDifferedBackground(PxPos position, sf::Texture* txt)
{
	engine->setDifferedBackground(position, txt);

	return this;
}

InitializedEngine* PxMatchGameFacade::resetDifferedBackground(PxPos position)
{
	engine->resetDifferedBackground(position);

	return this;
}

InitializedEngine* PxMatchGameFacade::draw(sf::RenderWindow* app)
{
	engine->drawMap(app);

	return this;
}


InitializedEngine* PxMatchGameFacade::swapPawnsAndMatch(PxPos firstPos, PxPos secondPos)
{
	engine->swapPawnsAndMatch(firstPos, secondPos);

	return this;
}



