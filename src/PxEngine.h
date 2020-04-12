#pragma once

#include "PatternsBase.h"

#include <vector>
#include <map>
#include <set>


class PxEngine : public PxEngineBase
{
public:
	PxEngine();
	
	void setFieldPointMap(const std::map<PxPos, PxFieldPoint>& fieldPointMap);
	void enableMovementDirections(Movement2D dir);

	// virtual base pattern functionality
	void addPatternToMatch(PxPatternBase* pattern);
	void matchAllPatterns();

	// callback patterns functionality
	void addPatternToMatch(PatternCB_t pattern, ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction = nullptr);
	void checkPatterns();

	void setMovement(const PxPos firstPos, const PxPos secondPos);
	void setDifferedBackground(PxPos position, sf::Texture* txt);
	void resetDifferedBackground(PxPos position);


	std::vector<PxPos> getPatternMatchPoints(PatternCB_t pattern) const;
	std::map<PxPos, PxFieldPoint> getFieldPointMap() const;

	void drawMap(sf::RenderWindow* app);
	void swapTextures(sf::Sprite*, sf::Sprite*);

private:
	void resetMovement(PxPos prev, PxPos curr);
	bool isMovementPossible(const PxPos p1, const PxPos p2);

	std::map<PxPos, PxFieldPoint> fieldPointMap;
	std::vector<PxPos> matchPoints;
	std::vector<const PxPatternBase*> pxPatterns;

	PxPos firstPos;
	PxPos secondPos;


	struct PatternCB
	{
		PatternCB_t pattern;
		ActOnSuccessCB_t matchingAction;
		ActOnFailCB_t failureAction;
	};

	std::vector<PatternCB> patterns;

	struct Move2D
	{
		bool isDxEnabled = false;
		bool isDyEnabled = false;
		bool isDxyEnabled = false;
	} move2d;
};
