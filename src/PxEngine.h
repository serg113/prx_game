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
	void setDifferedBackground(PxPos position) override;
	void resetDifferedBackground(PxPos position) override;

	// drawable
	void drawMap(sf::RenderWindow* app) override;

	// PatternMatchable
	void swapAndMatch(PxPos firstPos, PxPos secondPos) override;

private:
	void swapTextures(sf::Sprite*, sf::Sprite*);
	void dropDownPawns(PxPos position);
	void resetMovement(PxPos prev, PxPos curr);
	bool isMovementPossible(const PxPos p1, const PxPos p2);
	sf::Sprite* getBackgroundSprite(size_t X, size_t Y, bool isEven) const;
	sf::Sprite* getForegroundSprite(size_t X, size_t Y) const;
	bool checkPatternMatched(PxPos pos) const;

	Config params;

	std::map<PxPos, PxFieldPoint> fieldPointMap;
	std::vector<PxPattern*> enginePatterns;

};
