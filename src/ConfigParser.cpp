#include "ConfigParser.h"

#include <string>
#include <map>


std::string resFolder = "C:/Users/Sergey/Documents/_cpp/playrix/DevTestGame-master/resources/";

size_t tileSize = 87;
size_t figureSize = 60;
size_t rowCount = 5;
size_t columnCount = 5;
size_t startPosX = 100;
size_t startPosY = 100;

std::string bgTextureSrc1 = resFolder + "tile_1.png";
std::string bgTextureSrc2 = resFolder + "tile_2.png";
std::string bgPressedTextureSrc = resFolder + "tile_3.png";

std::string pawnRedSrc = resFolder + "red.png";
std::string pawnBlueSrc = resFolder + "blue.png";
std::string pawnGreenSrc = resFolder + "green.png";
std::string pawnVioletSrc = resFolder + "violet.png";

std::vector<std::string> textureSrc = { bgTextureSrc1, bgTextureSrc2, bgPressedTextureSrc };
std::map<BackgroundType, std::string> bgTileSrc;

size_t getBgTileSize() { return tileSize; }
size_t getPawnSize() { return figureSize; }
size_t getRowCount() { return rowCount; }
size_t getColumnCount() { return columnCount; }
size_t getStartPosX() { return startPosX; }
size_t getStartPosY() { return startPosY; }

void initConfig()
{
	bgTileSrc.emplace(BackgroundType::Type1, bgTextureSrc1);
	bgTileSrc.emplace(BackgroundType::Type2, bgTextureSrc2);
	bgTileSrc.emplace(BackgroundType::FieldChecked, bgPressedTextureSrc);
}

sf::Texture getBackgroundTexture(BackgroundType bgType)
{
	sf::Texture txt;

	if (!txt.loadFromFile(bgTileSrc[bgType]))
		throw std::exception("[config error] cannot load texture from source: /src/");

	return txt;
}

//Texture getPawnTextureByColor(TileColor color)

//Texture bgTexture1, bgTexture2, bgTexture3, greenFigure, redFigure, blueFigure, violetFigure;
//
//texture_1.loadFromFile(resFolder + "tile_1.png");
//texture_2.loadFromFile(resFolder + "tile_2.png");
//texture_3.loadFromFile(resFolder + "tile_3.png");
//
//greenFigure.loadFromFile(resFolder + "green.png");
//blueFigure.loadFromFile(resFolder + "blue.png");
//redFigure.loadFromFile(resFolder + "red.png");
//violetFigure.loadFromFile(resFolder + "violet.png");

// end of config