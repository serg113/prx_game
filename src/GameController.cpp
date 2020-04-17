#include <SFML/Graphics.hpp>
#include "GameController.hpp"

#include "PxConfiguration.h"
#include "PxMatchGame.h"

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

struct Pos
{
	size_t X;
	size_t Y;
	bool isValid;
};

Pos getPositionByCoordinates(int x, int y)
{
	Pos position;

	if (x > 100 && y > 100)
		position.isValid = true;
	else
		position.isValid = false;

	position.X = static_cast<size_t>((x - 100) / 87);
	position.Y = static_cast<size_t>((y - 100) / 87);

	return position;
}


void GameController::run() 
{
	/*
		Board row/column size. (min 7, max 10)
		Moves count.
		Objectives count (max 3) their colors and values. i.e. 10 red, 12 green, 20 blue.
		Figures colors count. (min 3, max 5)

	*/
	
	// config comes from server in json format

	std::string configString = "{"
		"boardSize:7,"
		"moveCount:5,"
		"objectives:[{red:10,green:12,blue:20}]"
		"figureColorCount:5"
		"}";

	// issue 1, choose json library to parse config string 

	mapJson configJson = { { "boardSize",7 }, {"moveCount",5},{"figureColorCount",5} };

	PxConfiguration options(configJson);

	auto matchGame = createGame(options);
    
	while (_app->isOpen()) {
        _app->clear(Color(150, 250, 150, 255));
		
		matchGame->draw(_app);
		
        sf::Event event;
        while (_app->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                _app->close();

			if (event.type == sf::Event::MouseButtonReleased)
			{
				matchGame->touch(event.mouseButton.x, event.mouseButton.y);
	
			}
			
        }
        _app->display();
    }
}
