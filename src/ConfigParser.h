#pragma once

#include <SFML/Graphics.hpp>


enum class TileType {
	NoType,
	BackGroundType1, 
	BackGroundType2, 
	BackGroundType3,
	RedPawn, 
	GreenPawn, 
	BluePawn, 
	VioletPawn
};

void initConfig();

size_t getPownCount();
size_t getBgTileSize();
size_t getPawnSize();
size_t getRowCount();
size_t getColumnCount();
size_t getStartPosX();
size_t getStartPosY();


sf::Texture getTexture(TileType tType);


