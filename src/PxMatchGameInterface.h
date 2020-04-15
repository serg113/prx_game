#pragma once 

#include "PxPatternInterface.h"
#include "PxTypes.h"

class InitializedEngine
{
public:
	virtual InitializedEngine* draw(sf::RenderWindow* app) = 0;
	virtual InitializedEngine* swapFigures(PxPoint pos1, PxPoint pos2) = 0;
	virtual InitializedEngine* setPositionIsChecked(PxPoint position) = 0;
	virtual InitializedEngine* setPositionUnChecked(PxPoint position) = 0;
};

class UnInitializedEngine
{
public:
	virtual UnInitializedEngine* setConfig(const Config& params) = 0;
	virtual InitializedEngine* initGameMap() = 0;
};

InitializedEngine* initEngine(const Config& options);