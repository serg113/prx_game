#pragma once
#include <SFML/Graphics.hpp>

#include "PxPatternInterface.h"
#include "PxTypes.h"


class Drawable
{
public:
	virtual void drawMap(sf::RenderWindow* app) = 0;
};

class PatternMatchable
{
public:
	virtual void swapAndMatch(PxPos firstPos, PxPos secondPos) = 0;
};

/* abstract base class for engine */
class PxEngineInterface
{
public:
	virtual void setConfig(const Config& params) = 0;
	virtual void initGameMap() = 0;

	virtual void setDifferedBackground(PxPos position) = 0;
	virtual void resetDifferedBackground(PxPos position) = 0;
};

