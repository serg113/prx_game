#include "PxConfiguration.h"
#include "PxGame.h"

#include <SFML/Graphics.hpp>
#include "GameController.hpp"


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

void GameController::run() 
{
	// read configs into a map and pass them to construct configurations
	mapJson configJson = { { "boardSize",7 }, {"moveCount",5}, {"figureColorCount",5},
							{"objRed", 21}, {"objBlue", 15 }, {"objGreen",  6} };

	PxConfiguration options(configJson);

	auto matchGame = createGame(options);
    
	while (_app->isOpen()) {
        _app->clear(Color(150, 250, 150, 255));

		matchGame->draw(_app);
		
        sf::Event event;
        while (_app->pollEvent(event)) {

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
