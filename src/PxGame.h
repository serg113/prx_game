#pragma once
#include "PxConfiguration.h"
#include <SFML/Graphics.hpp>


class InitializedGame
{
public:
	virtual InitializedGame* draw(sf::RenderTarget* app) = 0;
	virtual InitializedGame* touch(int x, int y) = 0;
};

InitializedGame* createGame(const PxConfiguration options);