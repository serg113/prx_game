#pragma once

#include "PxEngineBase.h"


class PxEngineFacade: public InitializedEngine, public UnInitializedEngine
{
public:
	PxEngineFacade();
	// initialization
	UnInitializedEngine* setConfigs(Config params);
	UnInitializedEngine* addPatternToMatch(PxPatternBase* pattern);
	InitializedEngine* initGameMap();

	// basic functionality of engine
	InitializedEngine* swapPawnsAndMatch(PxPos pos1, PxPos pos2);
	InitializedEngine* setDifferedBackground(PxPos position, sf::Texture* txt);
	InitializedEngine* resetDifferedBackground(PxPos position);

	// draw ui
	InitializedEngine* draw(sf::RenderWindow* app);

private:
	PxEngineBase* engine;

};



