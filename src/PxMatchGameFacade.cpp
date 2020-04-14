#include "PxMatchGameFacade.h"
#include "PxEngine.h"

#include <iostream>

PxMatchGameFacade::PxMatchGameFacade()
{
	engine = new PxEngine();
}

UnInitializedEngine* PxMatchGameFacade::setConfig(const Config& params)
{
	engine->setConfig(params);

	return this;
}

InitializedEngine* PxMatchGameFacade::initGameMap()
{
	engine->initGameMap();

	return this;
}

InitializedEngine* PxMatchGameFacade::setDifferedBackground(PxPos position)
{
	engine->setDifferedBackground(position);

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

	if (ptrDrawableEngine)
		ptrDrawableEngine->drawMap(app);
	else
		std::cout << "[cast failed] Engine is not Drawable" << std::endl;

	return this;
}


InitializedEngine* PxMatchGameFacade::swapFigures(PxPos firstPos, PxPos secondPos)
{
	PatternMatchable* ptrMatchableEngine = dynamic_cast<PatternMatchable*>(engine);

	if (ptrMatchableEngine)
		ptrMatchableEngine->swapAndMatch(firstPos, secondPos);
	else
		std::cout << "[cast failed] Engine is not PatternMatchable" << std::endl;

	return this;
}



