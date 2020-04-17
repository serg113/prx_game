#include "PxConfiguration.h"

#include <string>
#include <map>

// configJson = { { "boardSize",7 }, {"moveCount",5},{"figureColorCount",5} };

PxConfiguration::PxConfiguration(const mapJson& json): configJson(json)
{
	// possible case is to create default configs for other parameters

	resourceFolder = "C:/Users/Sergey/Documents/_cpp/playrix/DevTestGame-master/resources/";

	backgroundImgSrc = {
		resourceFolder + "tile_1.png",
		resourceFolder + "tile_2.png",
		resourceFolder + "tile_3.png",
	};

	foregroundImgSrc = {
		resourceFolder + "red.png",
		resourceFolder + "blue.png",
		resourceFolder + "green.png",
		resourceFolder + "orange.png",
		resourceFolder + "violet.png"
	};
}

const sf::Texture* PxConfiguration::backgroundTexture(size_t index) const
{
	return createTextureFromFile(backgroundImgSrc[index]);
}

const sf::Texture* PxConfiguration::foregroundTexture(size_t index) const
{
	return createTextureFromFile(foregroundImgSrc[index]);
}

size_t PxConfiguration::boardStartX() const
{
	return 100;
}

size_t PxConfiguration::boardStartY() const
{
	return 100;
}

size_t PxConfiguration::boardSize() const
{
	return configJson.at("boardSize");
}

size_t PxConfiguration::fieldSize() const
{
	return 87;
}

size_t PxConfiguration::figureSize() const
{
	return 60;
}

size_t PxConfiguration::figureColorCount() const
{
	return configJson.at("figureColorCount");
}

const sf::Texture* PxConfiguration::createTextureFromFile(const std::string& path) const
{
	auto texture = new sf::Texture();

	if (!texture->loadFromFile(path))
		throw std::exception("[config error] cannot load texture from source: /src/");

	return texture;
}

