#pragma once

#include "PxMatchGameInterface.h"
#include "PxEngineInterface.h"


class PxMatchGameFacade: public InitializedEngine, public UnInitializedEngine
{
public:
	PxMatchGameFacade();
	// initialization
	UnInitializedEngine* setConfig(const Config& params) override;
	InitializedEngine* initGameMap() override;

	// basic functionality of engine
	InitializedEngine* swapFigures(PxPos pos1, PxPos pos2) override;
	InitializedEngine* setDifferedBackground(PxPos position) override;
	InitializedEngine* resetDifferedBackground(PxPos position) override;

	// draw ui
	InitializedEngine* draw(sf::RenderWindow* app) override;

private:
	PxEngineInterface* engine;

};



