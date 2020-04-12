#pragma once
// need to be renemed to EngineBase.h
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>


class PxEngineBase
{
public:
	virtual ~PxEngineBase() = default;
};

class PxPos;

class PatternFailureInterface
{
public:
	virtual void resetMovement(PxPos prev, PxPos curr) = 0;
};

class PatternSuccessInterface
{
public:
	virtual void deleteMatchingPoints(std::vector<PxPos> points) = 0;
};

class IPatternMatchable2D
{
public:
	virtual std::vector<PxPos> matchThreeInSequenceDirectionX() = 0;
	virtual std::vector<PxPos> matchThreeInSequenceDirectoryY() = 0;
	virtual std::vector<PxPos> matchFourInSquare() = 0;
	virtual std::vector<PxPos> matchTypeT() = 0;
};

class PxPos 
{
public:
	PxPos();
	PxPos(size_t x, size_t y);
	size_t X;
	size_t Y;
};
bool operator<(const PxPos& lhs, const PxPos& rhs);

struct PxFieldPoint
{
	PxFieldPoint() = default;
	PxFieldPoint(sf::Sprite* back, sf::Sprite* front);
	sf::Sprite* bgTile;
	const sf::Texture* bgTxt;
	sf::Sprite* pawn;
};

enum class Movement2D {DX, DY, DXY};

typedef std::vector<PxPos>(*PatternCB_t)(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos);
typedef void(*ActOnSuccessCB_t)(std::map<PxPos, PxFieldPoint>&, std::vector<PxPos>);
typedef void(*ActOnFailCB_t)(PxPos prev, PxPos curr);


std::vector<PxPos> matchThreeInSequenceDirectionX(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints);



