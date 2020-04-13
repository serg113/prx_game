#pragma once 

#include "PxPatternInterface.h"
#include "PxTypes.h"

class InitializedEngine
{
public:
	virtual InitializedEngine* swapPawnsAndMatch(PxPos pos1, PxPos pos2) = 0;
	virtual InitializedEngine* setDifferedBackground(PxPos position, sf::Texture* txt) = 0;
	virtual InitializedEngine* resetDifferedBackground(PxPos position) = 0;
	virtual InitializedEngine* draw(sf::RenderWindow* app) = 0;
};

class UnInitializedEngine
{
public:
	virtual UnInitializedEngine* setConfigs(Config params) = 0;
	virtual UnInitializedEngine* addPatternToMatch(PxPattern* pattern) = 0;
	virtual InitializedEngine* initGameMap() = 0;
};

UnInitializedEngine* getEngine();