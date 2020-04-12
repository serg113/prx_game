#pragma once

#include "PatternsBase.h"


class PxEngineFacade
{
public:
	PxEngineFacade();
	PxEngineFacade* setConfigs(Config params);
	PxEngineFacade* addPatternToMatch(PxPatternBase* pattern);
	PxEngineFacade* initGameMap(); 
	// this step ends board initialization, need to change return interface to InitializedEngine

	PxEngineFacade* draw(sf::RenderWindow* app);

	// based on abstract base pattern functionality
	PxEngineFacade* matchAllPatterns();

	// callback case 
	PxEngineFacade* addPatternToMatch(PatternCB_t pattern, ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction = nullptr);
	PxEngineFacade* checkPatterns();

	PxEngineFacade* swapPawns(PxPos pos1, PxPos pos2);
	PxEngineFacade* setDifferedBackground(PxPos position, sf::Texture* txt);
	PxEngineFacade* resetDifferedBackground(PxPos position);


private:
	PxEngineBase* engine;

};

