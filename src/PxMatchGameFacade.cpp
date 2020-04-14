#include "PxMatchGameFacade.h"
#include "PxEngine.h"

#include <iostream>

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
	Drawable* ptrDrawableEngine = dynamic_cast<Drawable*>(engine);

	if (ptrDrawableEngine == nullptr)
		std::cout << "[cast error] Engine is not Drawable" << std::endl;
	else
		ptrDrawableEngine->drawMap(app);

	return this;
}


InitializedEngine* PxMatchGameFacade::swapPawnsAndMatch(PxPos firstPos, PxPos secondPos)
{
	PatternMatchable* ptrMatchableEngine = dynamic_cast<PatternMatchable*>(engine);

	if (ptrMatchableEngine == nullptr)
		std::cout << "[cast error] Engine is not PatternMatchable" << std::endl;
	else
		ptrMatchableEngine->swapAndMatchThreeInSequence(firstPos, secondPos);

	return this;
}



