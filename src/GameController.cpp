#include <SFML/Graphics.hpp>
#include "GameController.hpp"

#include "ConfigParser.h"
#include "PxMatchGameInterface.h"

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
    _app->setFramerateLimit(10);
    run();
}


void GameController::run() {
	
	initConfig();

	// init config to pass into engine
	Config initParams;

	initParams.boardStartPosX = getStartPosX();
	initParams.boardStartPosY = getStartPosY();
	initParams.rowCount = getRowCount();
	initParams.columnCount = getColumnCount();
	initParams.bgTileSize = getBgTileSize();
	initParams.figureSize = getPawnSize();

	initParams.backgroundTxts = { 
		getTexture(TileType::BackGroundType1), 
		getTexture(TileType::BackGroundType2), 
		getTexture(TileType::BackGroundType3) 
	};

	initParams.figureTxts = { 
		getTexture(TileType::RedPawn), 
		getTexture(TileType::GreenPawn), 
		getTexture(TileType::BluePawn), 
		getTexture(TileType::VioletPawn) 
	};


	auto engine = createEngine(initParams);

	PxPos prevPosition;
	bool isPrevPosValid = false;
    
	while (_app->isOpen()) {
        _app->clear(Color(150, 250, 150, 255));
		
		engine->draw(_app);
		
        sf::Event event;
        while (_app->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                _app->close();

			if (event.type == sf::Event::MouseButtonReleased)
			{
				auto point = getPositionByCoordinates(event.mouseButton.x, event.mouseButton.y);

				if (!point.isValid)
				{
					engine->resetDifferedBackground(prevPosition);

					isPrevPosValid = false;
				}
				else
				{
					PxPos currentPosition(point.X, point.Y);

					if (isPrevPosValid)
					{
						engine->swapFigures(prevPosition, currentPosition)
							->resetDifferedBackground(prevPosition);

						isPrevPosValid = false;
					}
					else
					{
						prevPosition = currentPosition;

						engine->setDifferedBackground(prevPosition);

						isPrevPosValid = true;

					}

				}

				
			}
			
        }
        _app->display();
    }
}


/*
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

	_app->draw(text);
*/