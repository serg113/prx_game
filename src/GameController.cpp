#include <SFML/Graphics.hpp>
#include "GameController.hpp"

#include "ConfigParser.h"
#include "PxEngineBase.h"

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

	// init config to pass into engine
	Config initParams;

	initParams.boardStartPosX = getStartPosX();
	initParams.boardStartPosY = getStartPosY();
	initParams.rowCount = getRowCount();
	initParams.columnCount = getColumnCount();
	initParams.bgTileSize = getBgTileSize();
	initParams.figureSize = getPawnSize();
	initParams.backgroundTxts = { &bgTxt1, &bgTxt2, &bgTxt3 };
	initParams.figureTxts = { &redTxt, &greenTxt, &blueTxt, &violetTxt };


	MatchThreeInDirectionXY matchDxy;

	auto engine = getEngine()
				->setConfigs(initParams)
				->addPatternToMatch(&matchDxy)
				->initGameMap();


	PxPos prevPosition;
	bool isPrevPosValid = false;
    
	while (_app->isOpen()) {
        _app->clear(Color(150, 250, 150, 255));
		_app->draw(text);

		engine->draw(_app);
		
        sf::Event event;
        while (_app->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                _app->close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				PxPos currentPosition;

				currentPosition.X = static_cast<int>((event.mouseButton.x - initParams.boardStartPosX) / initParams.bgTileSize);
				currentPosition.Y = static_cast<int>((event.mouseButton.y - initParams.boardStartPosY) / initParams.bgTileSize);

				if (isPrevPosValid)
				{
					engine->swapPawnsAndMatch(prevPosition, currentPosition)
						->resetDifferedBackground(prevPosition);

					isPrevPosValid = false;
				}
				else
				{
					prevPosition = currentPosition;

					engine->setDifferedBackground(prevPosition, &bgTxt3);
					
					isPrevPosValid = true;

				}
			}
			
        }
        _app->display();
    }
}


