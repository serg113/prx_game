#include "PxEngine.h"

#include "PxPattern.h"

#include <exception>
#include <iostream>
#include <cmath>
#include <random>


PxEngine::PxEngine() 
{
	enginePatterns.push_back(new MatchThreeInDirectionXY());
};

void PxEngine::setConfig(const Config& params)
{
	this->params = params;
}

void PxEngine::initGameMap()
{
	for (int i = 0; i < params.rowCount; ++i)
	{
		for (int j = 0; j < params.columnCount; ++j)
		{
			size_t posX = params.boardStartPosX + params.bgTileSize * i;
			size_t posY = params.boardStartPosY + params.bgTileSize * j;

			sf::Sprite* bgTile = getBackgroundSprite(posX, posY, (i + j) % 2);

			while (true)
			{
				sf::Sprite* pawn = getForegroundSprite(posX, posY);

				fieldPointMap.emplace(PxPos(i, j), PxFieldPoint(bgTile, pawn));

				if (!checkPatternMatched(PxPos(i, j)))
					break;

				fieldPointMap.erase(PxPos(i, j));				
			}
		}
	}
};

bool PxEngine::checkPatternMatched(PxPos pos) const
{
	for (auto pattern : enginePatterns)
		if (pattern->match(fieldPointMap, pos).size())
			return true;
	
	return false;
}

sf::Sprite* PxEngine::getForegroundSprite(size_t X, size_t Y) const 
{
	std::random_device rd; 

	float offset = (params.bgTileSize - params.figureSize) / 2.0; 

	size_t txtIndex = rd() % params.figureTxts.size();

	sf::Sprite* pawn = new sf::Sprite(*params.figureTxts[txtIndex]);

	pawn->setPosition(X + offset / 2, Y + offset / 2);

	return pawn;
}

sf::Sprite* PxEngine::getBackgroundSprite(size_t X, size_t Y, bool isEven) const
{	
	sf::Sprite* tile = new sf::Sprite(*params.backgroundTxts[isEven]);

	tile->setPosition(X, Y);

	return tile;
}


void PxEngine::setDifferedBackground(PxPos position)
{
	fieldPointMap[position].bgTxt = fieldPointMap[position].bgTile->getTexture();

	fieldPointMap[position].bgTile->setTexture(*params.backgroundTxts[2]);
}

void PxEngine::resetDifferedBackground(PxPos position)
{
	fieldPointMap[position].bgTile->setTexture(*fieldPointMap[position].bgTxt);
}


void PxEngine::swapTextures(sf::Sprite* lhs, sf::Sprite* rhs)
{
	const sf::Texture* temp = lhs->getTexture();
	lhs->setTexture(*(rhs->getTexture()), true);
	rhs->setTexture(*temp, true);
}

void PxEngine::resetMovement(PxPos prev, PxPos curr)
{
	swapTextures(fieldPointMap[prev].pawn, fieldPointMap[curr].pawn);
}

void PxEngine::drawMap(sf::RenderWindow* app)
{
	for (auto& point : fieldPointMap)
	{	
		if (point.second.bgTile != nullptr)
			app->draw(*point.second.bgTile);
		
		if (point.second.pawn != nullptr && point.second.isPawnVisible)
			app->draw(*point.second.pawn);
		
		if (!point.second.isPawnVisible)
		{
			dropDownPawns(point.first);

			for (auto& pattern : enginePatterns)
			{
				auto points = pattern->match(fieldPointMap, point.first);

				if (points.size())
					pattern->actOnSuccess(fieldPointMap, points); // erise figures 
			}
		}
	}
};

void PxEngine::dropDownPawns(PxPos position)
{
	std::random_device rd;

	auto& point = fieldPointMap[position];

	if (position.Y == 0)
	{
		point.pawn->setTexture(*params.figureTxts[rd() % params.figureTxts.size()], true);
		point.isPawnVisible = true;
		std::cout << "point : " << position.X << "-" << position.Y << std::endl;
	}
	else
	{
		auto itPoint = fieldPointMap.find({ position.X, position.Y - 1 });

		if (itPoint != fieldPointMap.end())
		{
			swapTextures(point.pawn, itPoint->second.pawn);

			point.isPawnVisible = !point.isPawnVisible;
			itPoint->second.isPawnVisible = !itPoint->second.isPawnVisible;
		}
	}
}

bool PxEngine::isMovementPossible(const PxPos p1, const PxPos p2)
{
	if ((p1.X < 0 || p2.X < 0) || (p1.Y < 0 || p2.Y < 0))
		return false;

	if ((abs((int)(p1.X - p2.X)) + abs((int)(p1.Y - p2.Y))) == 1)
		return true;

	return false;
}


void PxEngine::swapAndMatch(PxPos firstPos, PxPos secondPos)
{
	if (!isMovementPossible(firstPos, secondPos))
		return;

	swapTextures(fieldPointMap[firstPos].pawn, fieldPointMap[secondPos].pawn);

	for (auto& pattern : enginePatterns)
	{
		auto points = pattern->match(fieldPointMap, firstPos);
		auto points2 = pattern->match(fieldPointMap, secondPos);

		points.insert(points2.begin(), points2.end());

		if (points.size())
		{
			pattern->actOnSuccess(fieldPointMap, points); // erise figures 
		}
		else
		{
			pattern->actOnFailure(fieldPointMap, firstPos, secondPos); // re-swap figures
		}
	}
}