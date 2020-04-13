#pragma once

#include "PxMatchGameInterface.h"
#include "PxEngineInterface.h"


class PxMatchGameFacade: public InitializedEngine, public UnInitializedEngine
{
public:
	PxMatchGameFacade();
	// initialization
	UnInitializedEngine* setConfigs(Config params) override;
	UnInitializedEngine* addPatternToMatch(PxPattern* pattern) override;
	InitializedEngine* initGameMap() override;

	// basic functionality of engine
	InitializedEngine* swapPawnsAndMatch(PxPos pos1, PxPos pos2) override;
	InitializedEngine* setDifferedBackground(PxPos position, sf::Texture* txt) override;
	InitializedEngine* resetDifferedBackground(PxPos position) override;

	// draw ui
	InitializedEngine* draw(sf::RenderWindow* app) override;

private:
	PxEngineInterface* engine;

};



