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

class IResettableEngine
{
public:
	virtual void resetMovement() = 0;
};

class IPatternMatchable2D
{
public:
	virtual void matchThreeInSequenceDirectionX() = 0;
	virtual void matchThreeInSequenceDirectoryY() = 0;
	virtual void matchFourInSquare() = 0;
	virtual void matchTypeT() = 0;
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

typedef std::vector<PxFieldPoint>(*PatternCB_t)(std::map<PxPos, PxFieldPoint>, PxFieldPoint);
typedef void(*ActOnSuccessCB_t)(IPatternMatchable2D* engine);
typedef void(*ActOnFailCB_t)(IResettableEngine* engine);
