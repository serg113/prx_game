#include "PxEngine.h"

#include <exception>
#include <iostream>
#include <cmath>



PxEngine::PxEngine() {};


void PxEngine::addPatternToMatch(PxPatternBase* pattern)
{
	pxPatterns.push_back(pattern);
}

void PxEngine::matchAllPatterns()
{
	for (auto pxPat : pxPatterns)
	{
		auto points = pxPat->match(fieldPointMap, firstPos, secondPos);

		if (points.size())
			pxPat->actOnSuccess(fieldPointMap, points);
		else
			pxPat->actOnFailure(fieldPointMap, firstPos, secondPos);
	}
}


void PxEngine::addPatternToMatch(PatternCB_t pattern, ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction)
{
	patterns.push_back({ pattern, matchingAction, failureAction });
}

void PxEngine::checkPatterns()
{
	std::vector<PxPos> points;
	for (auto patt_cb : patterns)
	{
		auto fPoints = patt_cb.pattern(fieldPointMap, firstPos);
		points.insert(points.end(), fPoints.begin(), fPoints.end());

		auto sPoints = patt_cb.pattern(fieldPointMap, secondPos);
		points.insert(points.end(), sPoints.begin(), sPoints.end());
	
		if (points.size() > 0)
			patt_cb.matchingAction(fieldPointMap, points);
		else
			resetMovement(firstPos, secondPos);
	}
}


void PxEngine::setDifferedBackground(PxPos position, sf::Texture* txt)
{
	fieldPointMap[position].bgTxt = fieldPointMap[position].bgTile->getTexture();

	fieldPointMap[position].bgTile->setTexture(*txt);
}

void PxEngine::resetDifferedBackground(PxPos position)
{
	fieldPointMap[position].bgTile->setTexture(*fieldPointMap[position].bgTxt);
}


void PxEngine::enableMovementDirections(Movement2D dir) // not implemented
{
	switch (dir)
	{
	case Movement2D::DX: move2d.isDxEnabled = true;
	case Movement2D::DY: move2d.isDyEnabled = true;
	case Movement2D::DXY: move2d.isDxyEnabled = true;
	}
}

void PxEngine::setFieldPointMap(const std::map<PxPos, PxFieldPoint>&  fPoints)
{
	fieldPointMap = fPoints;
}

void PxEngine::setMovement(const PxPos p1, const PxPos p2)
{
	if (!isMovementPossible(p1, p2))
		return;

	firstPos = p1;
	secondPos = p2;

	swapTextures(fieldPointMap[p1].pawn, fieldPointMap[p2].pawn);
}

void PxEngine::swapTextures(sf::Sprite* lhs, sf::Sprite* rhs)
{
	const sf::Texture* temp = lhs->getTexture();
	lhs->setTexture(*(rhs->getTexture()), true);
	rhs->setTexture(*temp, true);
}


std::vector<PxPos> PxEngine::getPatternMatchPoints(PatternCB_t pattern) const
{
	return this->matchPoints;
}

std::map<PxPos, PxFieldPoint> PxEngine::getFieldPointMap() const
{
	return this->fieldPointMap;
}

void PxEngine::resetMovement(PxPos prev, PxPos curr)
{
	swapTextures(fieldPointMap[prev].pawn, fieldPointMap[curr].pawn);
}

void PxEngine::drawMap(sf::RenderWindow* app)
{
	for (auto point : fieldPointMap)
	{
		if(point.second.bgTile != nullptr)
			app->draw(*(point.second.bgTile));
		if(point.second.pawn != nullptr)
			app->draw(*(point.second.pawn));
	}
};

bool PxEngine::isMovementPossible(const PxPos p1, const PxPos p2)
{
	if ((p1.X < 0 || p2.X < 0) || (p1.Y < 0 || p2.Y < 0))
		return false;

	if ((abs((int)(p1.X - p2.X)) + abs((int)(p1.Y - p2.Y))) == 1)
		return true;

	return false;
}