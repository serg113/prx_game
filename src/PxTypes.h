#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>


/* config structure for engine */
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

/* coordinate of field positions represented by row and column numbers */
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
