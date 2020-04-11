#pragma once
#include <SFML/Graphics.hpp>

#include "PatternsBase.h"

#include <vector>
#include <map>


// note: pattern can be described by interfaces, 
//		 for accepting some pattern behavior, 
//       engine class need to implement appropriate interface


// usage sample

//		engine.setMovement(from, to)
//				.checkPattern(threeInSequence)
//					.performMatchingAction(dropItems, resetMovement)

class PxEngine;

void PxDraw(PxEngine* engine, sf::RenderWindow* app);

struct PxPos
{
	size_t X = 0;
	size_t Y = 0;
};

struct PxFieldPoint 
{
	PxPos pos;
	sf::Sprite* bgTile;
	sf::Sprite* pawn;
};


class PxEngine : public PxEngineBase, public IResettableEngine, public IPatternMatchable2D
{
public:
	virtual void resetMovement() override;
	virtual void matchThreeInSequenceDirectionX() override;
	virtual void matchThreeInSequenceDirectoryY() override;
	virtual void matchFourInSquare() override;
	virtual void matchTypeT() override;


	void setMovement(PxPos firstPos, PxPos secondPos);
	void checkPattern(PatternCB_t pattern);
	void performMatchingAction(ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction);

	std::vector<PxFieldPoint> getPatternMatchPoints(PatternCB_t pattern) const;
	std::map<PxPos, PxFieldPoint> getFieldPointMap() const;
	std::vector<PxFieldPoint> getFieldPoints() const;

private:
	std::map<PxPos, PxFieldPoint> fieldPointMap;
	std::vector<PxFieldPoint> fieldPoints;
	std::vector<PxFieldPoint> matchPoints;

	PxPos firstPos;
	PxPos secondPos;
};







/*
	pattern
	1. check if 3 horizontal elements equality comparer gives true
	the elements compose sequence that includes provided one

	comparator -- bool(*fn)(Pawn, Pawn), [](Pawn a, Pawn b){return a.color == b.color;}
				  is based on pawn color, can be lambda expression


	list<Pawn> pawns;

	std::vector<Movable2D> processPattrernName(Movable2D pawn, comparator cmp)
	{
		std::vector<Movable2D> retValue;

		if(cmp(pawn.x, itX + 1)
		{
			if(cmp(itX, itX + 2)
				return (x, x+1, x+2);
			if(cmp(itX, itX - 1)
				return (x-1, x, x+1);
		}

		if(cmp(itX, itX - 1) && cmp(itX, itX - 2))
			return (x-2, x-1, x);

		return ();

	}

*/