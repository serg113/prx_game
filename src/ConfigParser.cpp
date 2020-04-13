#include "ConfigParser.h"

#include <string>
#include <map>


std::string resFolder = "C:/Users/Sergey/Documents/_cpp/playrix/DevTestGame-master/resources/";

size_t pawnCount = 4; // number of color images
size_t tileSize = 87;
size_t figureSize = 60;
size_t rowCount = 7;
size_t columnCount = 7;
size_t startPosX = 100;
size_t startPosY = 100;

std::string bgTextureSrc1 = resFolder + "tile_1.png";
std::string bgTextureSrc2 = resFolder + "tile_2.png";
std::string bgPressedTextureSrc = resFolder + "tile_3.png";

std::string pawnRedSrc = resFolder + "red.png";
std::string pawnBlueSrc = resFolder + "blue.png";
std::string pawnGreenSrc = resFolder + "green.png";
std::string pawnVioletSrc = resFolder + "violet.png";

std::map<TileType, std::string> tileImgSrc;

size_t getPawnCount() { return pawnCount; }
size_t getBgTileSize() { return tileSize; }
size_t getPawnSize() { return figureSize; }
size_t getRowCount() { return rowCount; }
size_t getColumnCount() { return columnCount; }
size_t getStartPosX() { return startPosX; }
size_t getStartPosY() { return startPosY; }

void initConfig()
{
	tileImgSrc.emplace(TileType::BackGroundType1, bgTextureSrc1);
	tileImgSrc.emplace(TileType::BackGroundType2, bgTextureSrc2);
	tileImgSrc.emplace(TileType::BackGroundType3, bgPressedTextureSrc);

	tileImgSrc.emplace(TileType::RedPawn, pawnRedSrc);
	tileImgSrc.emplace(TileType::BluePawn, pawnBlueSrc);
	tileImgSrc.emplace(TileType::GreenPawn, pawnGreenSrc);
	tileImgSrc.emplace(TileType::VioletPawn, pawnVioletSrc);
}


sf::Texture getTexture(TileType tType)
{
	sf::Texture txt;

	if (!txt.loadFromFile(tileImgSrc[tType]))
		throw std::exception("[config error] cannot load texture from source: /src/");

	return txt;
}

Pos getPositionByCoordinates(int x, int y)
{ 
	Pos position;
	
	if (x > startPosX && y > startPosY)
		position.isValid = true;
	else
		position.isValid = false;

	position.X = static_cast<size_t>((x - startPosX) / tileSize);
	position.Y = static_cast<size_t>((y - startPosY) / tileSize);

	return position;
}

