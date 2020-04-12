#pragma once
// need to be renemed to EngineBase.h
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <set>

/* config structure for engine 
 * provides initial configurations to engine
 */
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

/* base class for engine,
 * with aim to provide polimorphic behavior  
 */
class PxEngineBase
{
public:
	virtual ~PxEngineBase() = default;
};

/* coordinate of field position 
 * according to row and column number
 */
class PxPos 
{
public:
	PxPos();
	PxPos(size_t x, size_t y);
	size_t X;
	size_t Y;
};

bool operator<(const PxPos& lhs, const PxPos& rhs);


/* represents one square field of board 
 * with background and foreground (figure or pawn)
 */
struct PxFieldPoint
{
	PxFieldPoint() = default;
	PxFieldPoint(sf::Sprite* back, sf::Sprite* front);

	sf::Sprite* bgTile;
	const sf::Texture* bgTxt;
	sf::Sprite* pawn;
	bool isPawnVisible = true;
};


/* base class with pure virtual mehtods
 * custom pattern need to be derived from this base 
 
 * three functions provide basic functionality 
 * to match pattern and subsequent actions 
 * if pattern successfully matched or failed to match 
 * 
 */
class PxPatternBase
{
public:
	/* returns matching positions according to pattern combined for two swapped points */
	virtual std::set<PxPos> match(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const = 0;

	/* action that need to be performed if match() returns not empty set */
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const = 0;

	/* action that need to be performed if match() returns empty set */
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const = 0;
};


/* concrete implementation of pattern base */

/* matching three points in sequence */
class MatchThreeInDirectionXY : public PxPatternBase
{
public:
	virtual std::set<PxPos> match(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;
	virtual void actOnSuccess(std::map<PxPos, PxFieldPoint>& fieldMap, std::set<PxPos>& points) const override;
	virtual void actOnFailure(std::map<PxPos, PxFieldPoint>& fieldMap, PxPos position1, PxPos position2) const override;
};


std::vector<PxPos> matchThreeInSequenceDirectionXY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionX(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);
std::vector<PxPos> matchThreeInSequenceDirectionY(std::map<PxPos, PxFieldPoint>& fieldPointMap, PxPos position);

void deleteMatchingPoints(std::map<PxPos, PxFieldPoint>& fieldPointMap, std::vector<PxPos> matchPoints);

