#pragma once
// need to be renemed to EngineBase.h
#include <SFML/Graphics.hpp>

#include "PxTypes.h"

#include <set>


/* abstract base class for any pattern acceptable by engine */
class PxPattern
{
public:
	/* returns matching positions according to pattern combined for two swapped points */
	virtual std::set<PxPos> match(const std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position) const = 0;

	/* action that need to be performed if match() returns not empty set */
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const = 0;

	/* action that need to be performed if match() returns empty set */
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const = 0;
};

