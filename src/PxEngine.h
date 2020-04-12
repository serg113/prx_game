#pragma once

#include "PatternsBase.h"

#include <vector>
#include <map>
#include <set>


class PxEngine : public PxEngineBase
{
public:
	PxEngine();
	// initialization of engine
	void setConfigs(Config params);
	void addPatternToMatch(PxPatternBase* pattern);
	void initGameMap();
	// after this step, initialization ends, and board map ready to play 

	// engine basic functionality
	void swapPawns(const PxPos firstPos, const PxPos secondPos);
	void matchAllPatterns();
	void setDifferedBackground(PxPos position, sf::Texture* txt);
	void resetDifferedBackground(PxPos position);

	// draw ui
	void drawMap(sf::RenderWindow* app);

private:
	void swapTextures(sf::Sprite*, sf::Sprite*);
	void dropDownPawns(PxPos position);
	void resetMovement(PxPos prev, PxPos curr);
	bool isMovementPossible(const PxPos p1, const PxPos p2);


	Config params;
	PxPos firstPos;
	PxPos secondPos;

	std::map<PxPos, PxFieldPoint> fieldPointMap;
	std::vector<const PxPatternBase*> pxPatterns;

};
