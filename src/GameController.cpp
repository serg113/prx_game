#include <SFML/Graphics.hpp>
#include "GameController.hpp"

#include "ConfigParser.h"

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <map>
#include <exception>


using namespace sf;

GameController::GameController() {
}

void GameController::updateGameStatus(GameStatus &status) {
    _gameStatus = status;
}

void GameController::startGame() {
    _app = new RenderWindow(VideoMode(1080, 744), "Game", Style::Close);
    _app->setFramerateLimit(60);
    run();
}





struct Direction
{
	int toRight = 0;
	int toLeft = 0;
	int toUp = 0;
	int toDown = 0;
};

Direction checkDirectionByOneStep(const std::vector<Sprite>& figTiles, int row, int col, Direction prevDir)
{
	Direction dir;

	int columnCount = 5; // need to be setten as parameter accessed from getter function
	int rowCount = 5;
	int currIndex = row * columnCount + col;
	
	if (col > 0 && prevDir.toLeft >= 0)
		if (figTiles[row * columnCount + col - 1].getTexture() == figTiles[currIndex].getTexture())
			dir.toLeft = prevDir.toLeft + 1;
		else dir.toLeft = -1;
	else dir.toLeft = -1;

	if (col < columnCount - 1 && prevDir.toRight >= 0)
		if (figTiles[row * columnCount + col + 1].getTexture() == figTiles[currIndex].getTexture())
			dir.toRight = prevDir.toRight + 1;
		else dir.toRight = -1;
	else dir.toRight = -1;

	if (row > 0 && prevDir.toUp >= 0)
		if (figTiles[(row - 1) * columnCount + col].getTexture() == figTiles[currIndex].getTexture())
			dir.toUp = prevDir.toUp + 1;
		else dir.toUp = -1;
	else dir.toUp = -1;

	if (row < rowCount - 1 && prevDir.toDown >= 0)
		if (figTiles[(row + 1) * columnCount + col].getTexture() == figTiles[currIndex].getTexture())
			dir.toDown = prevDir.toDown + 1;
		else dir.toDown = -1;
	else dir.toDown = -1;

	return dir;
}

bool threeSequenceMatch(const std::vector<Sprite>& figTiles, int row, int col)
{
	/* here is 2 variants
		1. variant for 'in middle' case 
		2. and lateral position case

		for 1. checking opposite items on vertical and horizontal
		for 2. the same as 1, but continue in one direction

	 */
	int columnCount = 5; // need to be setten as parameter accessed from getter function
	int rowCount = 5;

	int currIndex = row * columnCount + col;

	Direction dir = checkDirectionByOneStep(figTiles, row, col, Direction());
	std::cout << "checked directionns are: " << dir.toDown << ":" << dir.toUp << "  "
		<< dir.toLeft << ":" << dir.toRight << std::endl;
	
	if (dir.toDown == 1 && dir.toUp == 1)
		return true;

	if (dir.toLeft == 1 && dir.toRight == 1)
		return true;

	return false;
		

}


struct FigureNode
{
	FigureNode(const Sprite & spr, TileColor color) : tile(spr), tColor(color) 
	{ 
	};

	FigureNode(Sprite && spr, TileColor color): tile(std::move(spr)), tColor(color)
	{ 
	};

	Sprite tile;
	
	TileColor tColor = TileColor::NoColor;
	// pointers to adjoint tiles similar color tiles
	FigureNode* upperNode = nullptr;
	FigureNode* lowerNode = nullptr;
	FigureNode* leftNode  = nullptr;
	FigureNode* rightNode = nullptr;
};

void setAdjoints(const std::vector<FigureNode*> figTiles)
{
	int rowCount = 5;
	int columnCount = 5;

	for (int row = 0; row < rowCount; ++row)
	{
		for (int col = 0; col < columnCount; ++col)
		{
			int upperRow = row - 1;
			if (upperRow > 0)
				figTiles[row * columnCount + col]->upperNode = figTiles[upperRow * columnCount + col];

			int lowerRow = row + 1;
			if (lowerRow < rowCount - 1)
				figTiles[row * columnCount + col]->lowerNode = figTiles[lowerRow * columnCount + col];

			int leftColumn = col - 1;
			if (leftColumn > 0)
				figTiles[row * columnCount + col]->leftNode = figTiles[row * columnCount + leftColumn];

			int rightColumn = col + 1;
			if (rightColumn < columnCount - 1)
				figTiles[row * columnCount + col]->rightNode = figTiles[row * columnCount + rightColumn];
		}
	}
}

bool checkMatching(const FigureNode* currentFig, const FigureNode* prevFig, TileColor color)
{
	if (prevFig->leftNode && prevFig->leftNode != currentFig)
	{
		if (prevFig->leftNode->tColor == color
			&& (prevFig->leftNode->leftNode  && prevFig->leftNode->leftNode->tColor == color))
			return true;

		if (prevFig->rightNode && prevFig->rightNode != currentFig 
			&& prevFig->rightNode->tColor == color)
			return true;
	}

	if (prevFig->rightNode && prevFig->rightNode != currentFig)
	{
		if (prevFig->rightNode->tColor == color
			&& (prevFig->rightNode->rightNode  && prevFig->rightNode->rightNode->tColor == color))
			return true;
	}

	if (prevFig->upperNode && prevFig->upperNode != currentFig)
	{
		if (prevFig->upperNode->tColor == color
			&& (prevFig->upperNode->upperNode  && prevFig->upperNode->upperNode->tColor == color))
			return true;

		if (prevFig->lowerNode && prevFig->lowerNode != currentFig
			&& prevFig->lowerNode->tColor == color)
			return true;
	}

	if (prevFig->lowerNode && prevFig->lowerNode != currentFig)
	{
		if (prevFig->lowerNode->tColor == color
			&& (prevFig->lowerNode->lowerNode  && prevFig->lowerNode->lowerNode->tColor == color))
			return true;
	}

	return false;

}

std::map<int, Sprite> tileMap;


void GameController::run() {
	std::string resFolder = "C:/Users/Sergey/Documents/_cpp/playrix/DevTestGame-master/resources/";

	sf::Font font;
	if (!font.loadFromFile(resFolder + "STENCIL.TTF"))
	{
		std::cout << "error occured during reading fonts" << std::endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("Keep  calm  and  hello  world");
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Underlined);

    Texture texture_1, texture_2, texture_3, greenFigure, redFigure, blueFigure, violetFigure;

	initConfig();

	texture_1 = getBackgroundTexture(BackgroundType::Type1);
	texture_2 = getBackgroundTexture(BackgroundType::Type2);
	texture_3 = getBackgroundTexture(BackgroundType::FieldChecked);

	greenFigure.loadFromFile(resFolder + "green.png");
	blueFigure.loadFromFile(resFolder + "blue.png");
	redFigure.loadFromFile(resFolder + "red.png");
	violetFigure.loadFromFile(resFolder + "violet.png");


	size_t tileSize   = getBgTileSize();
	size_t figureSize = getPawnSize();
	size_t rowCount = getRowCount();
	size_t columnCount  = getColumnCount();
	size_t startPosX = getStartPosX();
	size_t startPosY  = getStartPosY();

	std::vector<Sprite> tiles;

	tiles.reserve(rowCount * columnCount);

	Sprite tile;

	for (int i = 0; i < rowCount; ++i) 
	{
		for (int j = 0; j < columnCount; ++j) 
		{
			if ((i + j) % 2 == 0)
				tile = Sprite(texture_2);
			else
				tile = Sprite(texture_1);

			tile.setPosition(startPosX + tileSize * i, startPosY + tileSize * j);

			tiles.emplace_back(std::move(tile)); 
		}
	}

	std::vector<FigureNode*> figTiles;

	figTiles.reserve(rowCount * columnCount);

	float offset = (tileSize - figureSize) / 2.0;
	Sprite fig;
	std::random_device rd;
	TileColor color;
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			unsigned int figNo = rd();
			switch (figNo % 4)
			{
			case 0: 
				color = TileColor::Red;
				fig = Sprite(redFigure);			   //fig.setPosition(startPosX + tileSize * i + offset / 2, startPosY + tileSize * j + offset);
				break;
			case 1: 
				color = TileColor::Green;
				fig = Sprite(greenFigure);				 //fig.setPosition(startPosX + tileSize * i + offset / 2, startPosY + tileSize * j + offset / 2);
				break;
			case 2: 
				color = TileColor::Blue;
				fig = Sprite(blueFigure);				//fig.setPosition(startPosX + tileSize * i + offset/2 + 6, startPosY + tileSize * j + offset + 2);
				break;
			case 3: 
				color = TileColor::Violet;
				fig = Sprite(violetFigure);				//fig.setPosition(startPosX + tileSize * i + offset / 2, startPosY + tileSize * j + offset/2);
				break;
			default: 
				color = TileColor::Red;
				fig = Sprite(redFigure);				//fig.setPosition(startPosX + tileSize * i + offset / 2, startPosY + tileSize * j + offset);
			}

			fig.setPosition(startPosX + tileSize * i + offset/2, startPosY + tileSize * j + offset/2);
			
			figTiles.emplace_back(new FigureNode(fig, color));
		}
	}
	
	setAdjoints(figTiles);

	struct VFigure 
	{
		int index;
		bool is_valid = false;
		const Texture* texture;
		int row;
		int col;
		
	} prevSelection;
	
    
	while (_app->isOpen()) {
        _app->clear(Color(150, 250, 150, 255));
		_app->draw(text);
		
		for (auto& tile : tiles)
			_app->draw(tile);
		for (auto ft : figTiles)
			_app->draw(ft->tile);

        sf::Event event;
        while (_app->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                _app->close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;

				int row = static_cast<int>((event.mouseButton.x - startPosX) / tileSize);
				int column = static_cast<int>((event.mouseButton.y - startPosY) / tileSize);
				
				int tileIndex = row * columnCount + column;
				std::cout << "index = " << tileIndex << std::endl;

				if (!prevSelection.is_valid)
				{
					prevSelection.index = tileIndex;
					prevSelection.is_valid = true;
					prevSelection.texture = tiles[tileIndex].getTexture();
					prevSelection.row = row;
					prevSelection.col = column;

					tiles[tileIndex].setTexture(texture_3);
					_app->draw(tiles[tileIndex]);
				}
				else 
				{
					if (figTiles[prevSelection.index]->tColor != figTiles[tileIndex]->tColor)
					{
						// also check if adjoints

						if (checkMatching(figTiles[tileIndex], figTiles[prevSelection.index], figTiles[tileIndex]->tColor)
							|| checkMatching(figTiles[prevSelection.index], figTiles[tileIndex], figTiles[prevSelection.index]->tColor))
						{
							std::cout << "can be exchanged" << std::endl;
							const Texture* temp = figTiles[tileIndex]->tile.getTexture();
							figTiles[tileIndex]->tile.setTexture(*(figTiles[prevSelection.index]->tile.getTexture()), true);
							figTiles[prevSelection.index]->tile.setTexture(*temp, true);

							_app->draw(figTiles[tileIndex]->tile);
							_app->draw(figTiles[prevSelection.index]->tile);

						}
						else
						{
							/*const Texture* temp = figTiles[tileIndex]->tile.getTexture();
							figTiles[tileIndex]->tile.setTexture(*(figTiles[prevSelection.index]->tile.getTexture()), true);
							figTiles[prevSelection.index]->tile.setTexture(*temp, true);*/
						}
					}

					tiles[prevSelection.index].setTexture(*(prevSelection.texture));
					_app->draw(tiles[prevSelection.index]);
					prevSelection.is_valid = false;


				}

				

				//figTiles.erase(tiles.begin() + tileIndex);
				setAdjoints(figTiles);
			}
				
        }
        _app->display();
    }
}
