#pragma once 

#include "PxPatternInterface.h"
#include "PxTypes.h"

class InitializedEngine
{
public:
	virtual InitializedEngine* draw(sf::RenderWindow* app) = 0;
	virtual InitializedEngine* swapFigures(PxPos pos1, PxPos pos2) = 0;
	virtual InitializedEngine* setDifferedBackground(PxPos position) = 0;
	virtual InitializedEngine* resetDifferedBackground(PxPos position) = 0;
};

class UnInitializedEngine
{
public:
	virtual UnInitializedEngine* setConfig(const Config& params) = 0;
	virtual InitializedEngine* initGameMap() = 0;
};

InitializedEngine* initEngine(const Config& options);