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
	InitializedEngine* swapFigures(PxPoint pos1, PxPoint pos2) override;
	InitializedEngine* setPositionIsChecked(PxPoint position) override;
	InitializedEngine* setPositionUnChecked(PxPoint position) override;

	// draw ui
	InitializedEngine* draw(sf::RenderWindow* app) override;

private:
	PxEngineInterface* engine;

};



