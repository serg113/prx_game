#pragma once

#include "PxPatternInterface.h"
#include "PxTypes.h"

#include <SFML/Graphics.hpp>

/* concrete implementations of pattern interface */



/* matching three points in sequence */
class MatchThreeInDirectionXY : public PxPattern
{
public:
	virtual std::set<PxPoint> match(const std::map<PxPoint, PxField>& fieldMap, PxPoint position) const override;
	virtual void actOnSuccess(std::map<PxPoint, PxField>& fieldMap, std::set<PxPoint>& points) const override;
	virtual void actOnFailure(std::map<PxPoint, PxField>& fieldMap, PxPoint position1, PxPoint position2) const override;
};


std::vector<PxPoint> matchThreeInSequenceDirectionXY(const std::map<PxPoint, PxField>& fieldPointMap, PxPoint position);
std::vector<PxPoint> matchThreeInSequenceDirectionX(const std::map<PxPoint, PxField>& fieldPointMap, PxPoint position);
std::vector<PxPoint> matchThreeInSequenceDirectionY(const std::map<PxPoint, PxField>& fieldPointMap, PxPoint position);

void deleteMatchingPoints(std::map<PxPoint, PxField>& fieldPointMap, std::vector<PxPoint> matchPoints);

void swapTextures(sf::Sprite* lhs, sf::Sprite* rhs);