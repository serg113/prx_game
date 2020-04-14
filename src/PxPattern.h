#pragma once

#include <SFML/Graphics.hpp>

#include "PxPatternInterface.h"
#include "PxTypes.h"


/* concrete implementation of pattern interface */

/* matching three points in sequence */
class MatchThreeInDirectionXY : public PxPattern
{
public:
	virtual std::set<PxPos> match(const std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position) const override;
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const override;
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;
};


std::vector<PxPos> matchThreeInSequenceDirectionXY(const std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionX(const std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionY(const std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints);

void swapTextures(sf::Sprite* lhs, sf::Sprite* rhs);