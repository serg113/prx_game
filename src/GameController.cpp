#include <SFML/Graphics.hpp>
#include "GameController.hpp"

#include "ConfigParser.h"
#include "PxEngineFacade.h"

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

  
	initConfig();

	Texture bgTxt1, bgTxt2, bgTxt3, redTxt, greenTxt, blueTxt, violetTxt;

	bgTxt1 = getTexture(TileType::BackGroundType1);
	bgTxt2 = getTexture(TileType::BackGroundType2);
	bgTxt3 = getTexture(TileType::BackGroundType3);
	
	redTxt = getTexture(TileType::RedPawn);
	greenTxt = getTexture(TileType::GreenPawn);
	blueTxt = getTexture(TileType::BluePawn);
	violetTxt = getTexture(TileType::VioletPawn);

	size_t tileSize    = getBgTileSize();
	size_t figureSize  = getPawnSize();
	size_t rowCount    = getRowCount();
	size_t columnCount = getColumnCount();
	size_t startPosX   = getStartPosX();
	size_t startPosY   = getStartPosY();


	std::map<PxPos, PxFieldPoint> fieldPointsMap;

	
	float offset = (tileSize - figureSize) / 2.0;
	std::random_device rd;

	std::vector<Texture> pawnTextures = { redTxt, greenTxt, blueTxt, violetTxt };
	std::vector<TileType> pawnColors
		= { TileType::RedPawn, TileType::GreenPawn, TileType::BluePawn, TileType::VioletPawn };


	for (int i = 0; i < rowCount; ++i) 
	{
		for (int j = 0; j < columnCount; ++j) 
		{
			// background initialization part
			Sprite* tile;
			if ((i + j) % 2 == 0) 
				tile = new Sprite(bgTxt1);
			else
				tile = new Sprite(bgTxt2);

			tile->setPosition(startPosX + tileSize * i, startPosY + tileSize * j);

			fieldPointsMap.emplace(PxPos(i, j), PxFieldPoint(tile, nullptr));

			// foreground initialization part
			unsigned int pawnColorIndex = rd() % getPawnCount();

			Sprite* pawn = new Sprite(pawnTextures[pawnColorIndex]);

			pawn->setPosition(startPosX + tileSize * i + offset/2, startPosY + tileSize * j + offset/2);
			
			fieldPointsMap[PxPos(i, j)].pawn = pawn;
		}
	}
	

	PxEngineFacade engine;

	engine.setGameMap(fieldPointsMap)->enableMovement(Movement2D::DXY);

	PxPos prevPosition;
	bool isPrevPosValid = false;
    
	while (_app->isOpen()) {
        _app->clear(Color(150, 250, 150, 255));
		_app->draw(text);

		engine.draw(_app);
		
		

        sf::Event event;
        while (_app->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                _app->close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				int x = static_cast<int>((event.mouseButton.x - startPosX) / tileSize);
				int y = static_cast<int>((event.mouseButton.y - startPosY) / tileSize);

				if (isPrevPosValid)
				{
					engine.setMovement(prevPosition, PxPos(x, y));
					engine.draw(_app);
					isPrevPosValid = false;
				}
				else
				{
					prevPosition = PxPos(x, y);
					isPrevPosValid = true;
				}
			}
			/*
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
					prevSelection.texture = tiles[tileIndex]->getTexture();
					prevSelection.row = row;
					prevSelection.col = column;

					tiles[tileIndex]->setTexture(bgTxt3);
					_app->draw(*tiles[tileIndex]);
				}
				else 
				{
					if (pawns[prevSelection.index]->tColor != pawns[tileIndex]->tColor)
					{
						// also check if adjoints

						if (checkMatching(pawns[tileIndex], pawns[prevSelection.index], pawns[tileIndex]->tColor)
							|| checkMatching(pawns[prevSelection.index], pawns[tileIndex], pawns[prevSelection.index]->tColor))
						{
							std::cout << "can be exchanged" << std::endl;
							const Texture* temp = pawns[tileIndex]->tile.getTexture();
							pawns[tileIndex]->tile.setTexture(*(pawns[prevSelection.index]->tile.getTexture()), true);
							pawns[prevSelection.index]->tile.setTexture(*temp, true);

							_app->draw(pawns[tileIndex]->tile);
							_app->draw(pawns[prevSelection.index]->tile);

						}
						else
						{
							//const Texture* temp = figTiles[tileIndex]->tile.getTexture();
							//figTiles[tileIndex]->tile.setTexture(*(figTiles[prevSelection.index]->tile.getTexture()), true);
							//figTiles[prevSelection.index]->tile.setTexture(*temp, true);
						}
					}

					tiles[prevSelection.index]->setTexture(*(prevSelection.texture));
					_app->draw(*tiles[prevSelection.index]);
					prevSelection.is_valid = false;


				}

				

				//figTiles.erase(tiles.begin() + tileIndex);
				setAdjoints(pawns);
			}
			*/
        }
        _app->display();
    }
}


