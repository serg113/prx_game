#pragma once
#include <SFML/Graphics.hpp>

#include "PxPatternInterface.h"
#include "PxTypes.h"


/* abstract base class for engine */
class PxEngineInterface
{
public:
	virtual void setConfigs(Config params) = 0;
	virtual void addPatternToMatch(PxPattern* pattern) = 0;
	virtual void initGameMap() = 0;

	virtual void swapPawnsAndMatch(const PxPos firstPos, const PxPos secondPos) = 0;
	virtual void setDifferedBackground(PxPos position, sf::Texture* txt) = 0;
	virtual void resetDifferedBackground(PxPos position) = 0;

	virtual  void drawMap(sf::RenderWindow* app) = 0;
};

