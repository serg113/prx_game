#pragma once

#include "PatternsBase.h"


class PxEngineFacade
{
public:
	PxEngineFacade();
	// initialization
	PxEngineFacade* setConfigs(Config params);
	PxEngineFacade* addPatternToMatch(PxPatternBase* pattern);
	PxEngineFacade* initGameMap(); 
	// this step ends board initialization, need to change return interface to InitializedEngine

	// basic functionality of engine
	PxEngineFacade* swapPawns(PxPos pos1, PxPos pos2);
	PxEngineFacade* matchAllPatterns();
	PxEngineFacade* setDifferedBackground(PxPos position, sf::Texture* txt);
	PxEngineFacade* resetDifferedBackground(PxPos position);

	// draw ui
	PxEngineFacade* draw(sf::RenderWindow* app);

private:
	PxEngineBase* engine;

};

