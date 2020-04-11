#pragma once

#include "PatternsBase.h"

#include <vector>
#include <map>


class PxEngine : public PxEngineBase, public IResettableEngine, public IPatternMatchable2D
{
public:
	PxEngine();
	virtual void resetMovement() override;
	virtual void matchThreeInSequenceDirectionX() override;
	virtual void matchThreeInSequenceDirectoryY() override;
	virtual void matchFourInSquare() override;
	virtual void matchTypeT() override;

	void setDifferedBackground(PxPos position, sf::Texture* txt);
	void resetDifferedBackground(PxPos position);

	void enableMovementDirections(Movement2D dir);
	void setFieldPointMap(const std::map<PxPos, PxFieldPoint> fieldPointMap);
	void setMovement(const PxPos firstPos, const PxPos secondPos);
	void checkPattern(PatternCB_t pattern);
	void performMatchingAction(ActOnSuccessCB_t matchingAction, ActOnFailCB_t failureAction);

	std::vector<PxFieldPoint> getPatternMatchPoints(PatternCB_t pattern) const;
	std::map<PxPos, PxFieldPoint> getFieldPointMap() const;

	void drawMap(sf::RenderWindow* app);
	void swapTextures(sf::Sprite*, sf::Sprite*);

private:
	bool isMovementPossible(const PxPos p1, const PxPos p2);


	std::map<PxPos, PxFieldPoint> fieldPointMap;
	std::vector<PxFieldPoint> matchPoints;

	PxPos firstPos;
	PxPos secondPos;

	struct Move2D
	{
		bool isDxEnabled = false;
		bool isDyEnabled = false;
		bool isDxyEnabled = false;
	} move2d;
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