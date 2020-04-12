#pragma once

#include "PatternsBase.h"

#include <vector>
#include <map>
#include <set>


class PxEngine : public PxEngineBase
{
public:
	PxEngine();

	void setConfigs(Config params);
	void addPatternToMatch(PxPatternBase* pattern);
	void initGameMap();// after this step, initialization ends, and board map ready to play 

	void matchAllPatterns();

	void swapPawns(const PxPos firstPos, const PxPos secondPos);
	void setDifferedBackground(PxPos position, sf::Texture* txt);
	void resetDifferedBackground(PxPos position);

	void drawMap(sf::RenderWindow* app);
	void swapTextures(sf::Sprite*, sf::Sprite*);

	// callback patterns functionality, will be deleted at next iteration
	void addPatternToMatch(PatternCB_t pattern, ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction = nullptr);
	void checkPatterns();

	void dropDownPawns(PxPos position);

private:
	void resetMovement(PxPos prev, PxPos curr);
	bool isMovementPossible(const PxPos p1, const PxPos p2);

	std::map<PxPos, PxFieldPoint> fieldPointMap;
	std::vector<PxPos> matchPoints;
	std::vector<const PxPatternBase*> pxPatterns;

	PxPos firstPos;
	PxPos secondPos;

	Config params;

	// currently useless and may be deleted at next iteration
	struct PatternCB
	{
		PatternCB_t pattern;
		ActOnSuccessCB_t matchingAction;
		ActOnFailCB_t failureAction;
	};

	std::vector<PatternCB> patterns;

};
