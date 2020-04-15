#pragma once

#include "PxEngineInterface.h"
#include "PxPatternInterface.h"

#include <vector>
#include <map>


class PxEngine : public PxEngineInterface, public Drawable, public PatternMatchable
{
public:
	PxEngine();
	// initialization of engine
	void setConfig(const Config& params) override;
	void initGameMap();

	// engine functionality
	void setPositionIsChecked(PxPoint position) override;
	void setPositionUnChecked(PxPoint position) override;

	// Drawable
	void drawMap(sf::RenderWindow* app) override;

	// PatternMatchable
	void swapAndMatch(PxPoint firstPos, PxPoint secondPos) override;

private:
	void swapTextures(sf::Sprite*, sf::Sprite*); // move to utility functions
	void dropDownPawns(PxPoint position);
	bool isMovementPossible(const PxPoint p1, const PxPoint p2);
	sf::Sprite* getBackgroundSprite(size_t X, size_t Y, bool isEven) const;
	sf::Sprite* getForegroundSprite(size_t X, size_t Y) const;
	bool checkPatternMatched(PxPoint pos) const;

	Config params;

	std::map<PxPoint, PxField> fieldPointMap;
	std::vector<PxPattern*> enginePatterns;

};
