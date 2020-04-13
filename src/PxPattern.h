#pragma once
// need to be renemed to EngineBase.h
#include <SFML/Graphics.hpp>

#include "PxPatternInterface.h"
#include "PxTypes.h"


/* concrete implementation of pattern base */

/* matching three points in sequence */
class MatchThreeInDirectionXY : public PxPattern
{
public:
	virtual std::set<PxPos> match(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const override;
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;
};


std::vector<PxPos> matchThreeInSequenceDirectionXY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionX(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints);

void swapTextures(sf::Sprite* lhs, sf::Sprite* rhs);