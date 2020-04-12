#pragma once

#include "PatternsBase.h"


class PxEngineFacade
{
public:
	PxEngineFacade();
	PxEngineFacade* draw(sf::RenderWindow* app);
	PxEngineFacade* enableMovement(Movement2D dir);
	PxEngineFacade* setGameMap(std::map<PxPos, PxFieldPoint> fieldPointMap);

	// based on abstract base pattern functionality
	PxEngineFacade* addPatternToMatch(PxPatternBase* pattern);
	PxEngineFacade* matchAllPatterns();

	// callback case 
	PxEngineFacade* addPatternToMatch(PatternCB_t pattern, ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction = nullptr);
	PxEngineFacade* checkPatterns();

	PxEngineFacade* setMovement(PxPos start, PxPos end);
	PxEngineFacade* setDifferedBackground(PxPos position, sf::Texture* txt);
	PxEngineFacade* resetDifferedBackground(PxPos position);


private:
	PxEngineBase* engine;

};

