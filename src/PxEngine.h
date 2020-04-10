#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>

// to do : 1. add interfaces 

struct PxPos;
struct PxFieldPoint;
class PxEngine;

typedef std::vector<PxFieldPoint>(*Pattern_t)(std::map<PxPos, PxFieldPoint>, PxFieldPoint);

typedef void(*ActOnSuccess_t)(PxEngine* engine, std::vector<PxFieldPoint>);

typedef void(*ActOnFail_t)(PxEngine* engine, PxPos start, PxPos end);

void resetMovement(PxEngine* engine, PxPos start, PxPos end);
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

class PxEngine
{
public:
	PxEngine* setMovement(PxPos start, PxPos end);
	PxEngine* checkPattern(Pattern_t pattern);
	PxEngine* performMatchingAction(ActOnSuccess_t matchingAction, ActOnFail_t failureAction = resetMovement);


	std::vector<PxFieldPoint> getPatternMatchPoints(Pattern_t pattern) const;
	std::map<PxPos, PxFieldPoint> getFieldPointMap() const;
	std::vector<PxFieldPoint> getFieldPoints() const;

private:
	std::map<PxPos, PxFieldPoint> fieldPointMap;

	std::vector<PxFieldPoint> fieldPoints;
	std::vector<PxFieldPoint> matchPoints;

	PxPos exchStart;
	PxPos exchEnd;
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