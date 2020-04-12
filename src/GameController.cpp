#include <SFML/Graphics.hpp>
#include "GameController.hpp"

#include "ConfigParser.h"
#include "PxEngineFacade.h"

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <map>


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

			// foreground initialization part
			int counter = 0;
			while (counter < 100)
			{
				unsigned int pawnColorIndex = rd() % getPawnCount();

				Sprite* pawn = new Sprite(pawnTextures[pawnColorIndex]);

				pawn->setPosition(startPosX + tileSize * i + offset / 2, startPosY + tileSize * j + offset / 2);

				fieldPointsMap.emplace(PxPos(i, j), PxFieldPoint(tile, pawn));

				if (matchThreeInSequenceDirectionX(fieldPointsMap, PxPos(i, j)).size() == 0
					&& matchThreeInSequenceDirectionY(fieldPointsMap, PxPos(i, j)).size() == 0)
					break;
				counter++;
			}
		}
	}
	

	PxEngineFacade engine;
	MatchThreeInDirectionXY matchDxy;

	engine.setGameMap(fieldPointsMap)
		->enableMovement(Movement2D::DXY)
		->addPatternToMatch(&matchDxy);
		//->addPatternToMatch(&matchThreeInSequenceDirectionXY, &deleteMatchingPoints);
		//->addPatternToMatch(&matchThreeInSequenceDirectionY, &deleteMatchingPoints);
	

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
					engine.setMovement(prevPosition, PxPos(x, y))
						->matchAllPatterns()
						->resetDifferedBackground(prevPosition);

					isPrevPosValid = false;
				}
				else
				{
					prevPosition = PxPos(x, y);

					engine.setDifferedBackground(prevPosition, &bgTxt3);
					
					isPrevPosValid = true;

				}
			}
			
        }
        _app->display();
    }
}


