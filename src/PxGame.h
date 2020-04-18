#pragma once
#include "PxConfiguration.h"
#include <SFML/Graphics.hpp>


class InitializedGame
{
public:
	/**
	 * performs internal state rendering to target app
	 * @params app pointer to renderer object
	 * @returns pointer to this pxGame instance
	 */
	virtual InitializedGame* draw(sf::RenderTarget* app) = 0;

	/**
	 * performs response to touch action
	 * @params x,y coordinates of user interaction point
	 * @returns pointer to this pxGame instance
	 */
	virtual InitializedGame* touch(int x, int y) = 0;
};

/**
 * initializes game instance based on options
 * @params options configurations for pxGame instance
 * @returns pointer to pxGame instance
 */
InitializedGame* createGame(const PxConfiguration options);