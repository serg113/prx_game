#pragma once
// need to be renemed to EngineBase.h
#include <SFML/Graphics.hpp>

#include "PxTypes.h"

#include <set>


/* abstract base class for any pattern acceptable by engine */
class PxPattern
{

public:
	/* returns a set of matching points according to pattern */
	virtual std::set<PxPoint> match(const std::map<PxPoint, PxField>& fieldMap, PxPoint point) const = 0;

	/* action that need to be performed if match points set */
	virtual void actOnSuccess(std::map<PxPoint, PxField>& fieldMap, std::set<PxPoint>& matchPoints) const = 0;

	/* action that need to be performed if matching points set is empty */
	virtual void actOnFailure(std::map<PxPoint, PxField>& fieldMap, PxPoint point1, PxPoint point2) const = 0;
};

