#include "PxEngine.h"

#include <exception>
#include <iostream>
#include <cmath>
#include <random>



PxEngine::PxEngine() {};

void PxEngine::setConfigs(Config params)
{
	this->params = params;
}

void PxEngine::initGameMap()
{
	float offset = (params.bgTileSize - params.figureSize) / 2.0;

	std::random_device rd;

	for (int i = 0; i < params.rowCount; ++i)
	{
		for (int j = 0; j < params.columnCount; ++j)
		{
			size_t posX = params.boardStartPosX + params.bgTileSize * i;
			size_t posY = params.boardStartPosY + params.bgTileSize * j;

			// background initialization part
			sf::Sprite* tile;
			if ((i + j) % 2 == 0)  
				tile = new sf::Sprite(*params.backgroundTxts[0]);
			else
				tile = new sf::Sprite(*params.backgroundTxts[1]);

			tile->setPosition(posX, posY);

			// foreground initialization part
			unsigned int txtIndex = rd() % params.figureTxts.size();

			sf::Sprite* pawn = new sf::Sprite(*params.figureTxts[txtIndex]);

			pawn->setPosition(posX + offset / 2, posY + offset / 2);

			fieldPointMap.emplace(PxPos(i, j), PxFieldPoint(tile, pawn));

		}
	}
};


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
		{
			pxPat->actOnSuccess(fieldPointMap, points); // erise figures 
		}
		else
		{
			pxPat->actOnFailure(fieldPointMap, firstPos, secondPos); // re-swap figures
		}

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


void PxEngine::swapPawns(const PxPos p1, const PxPos p2)
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

void PxEngine::resetMovement(PxPos prev, PxPos curr)
{
	swapTextures(fieldPointMap[prev].pawn, fieldPointMap[curr].pawn);
}

void PxEngine::drawMap(sf::RenderWindow* app)
{
	std::random_device rd;

	for (auto& point : fieldPointMap)
	{
		if (point.second.bgTile != nullptr)
		{
			app->draw(*point.second.bgTile);
		}
		if (point.second.pawn != nullptr && point.second.isPawnVisible)
		{
			app->draw(*point.second.pawn);
		}

		if (!point.second.isPawnVisible)
		{
			dropDownPawns(point.first);
		}
	}
};

void PxEngine::dropDownPawns(PxPos position)
{
	auto& point = fieldPointMap[position];

	std::random_device rd;

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