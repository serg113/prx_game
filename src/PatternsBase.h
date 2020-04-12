#pragma once
// need to be renemed to EngineBase.h
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <set>

struct Config
{
	std::vector<sf::Texture*> backgroundTxts;
	std::vector<sf::Texture*> figureTxts;
	size_t boardStartPosX;
	size_t boardStartPosY;
	size_t rowCount;
	size_t columnCount;
	size_t bgTileSize;
	size_t figureSize;

};

class PxEngineBase
{
public:
	virtual ~PxEngineBase() = default;
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
	bool isPawnVisible = true;
};

enum class Movement2D {DX, DY, DXY};

// pattern base
class PxPatternBase
{
public:
	virtual std::set<PxPos> match(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const = 0;
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const = 0;
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const = 0;
};

// concrete implementation of pattern base
class MatchThreeInDirectionXY : public PxPatternBase
{
public:
	virtual std::set<PxPos> match(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const override;
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;

};

// callback implementation case
typedef std::vector<PxPos>(*PatternCB_t)(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos);
typedef void(*ActOnSuccessCB_t)(std::map<PxPos, PxFieldPoint>&, std::vector<PxPos>);
typedef void(*ActOnFailCB_t)(PxPos prev, PxPos curr);

std::vector<PxPos> matchThreeInSequenceDirectionXY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionX(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints);

class IPatternMatchable2D
{
public:
	virtual std::vector<PxPos> matchThreeInSequenceDirectionX() = 0;
	virtual std::vector<PxPos> matchThreeInSequenceDirectoryY() = 0;
	virtual std::vector<PxPos> matchFourInSquare() = 0;
	virtual std::vector<PxPos> matchTypeT() = 0;
};
