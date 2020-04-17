#pragma once

#include "PxTypes.h"

#include <SFML/Graphics.hpp>
#include <string>


// json comes from server 
// app reads json and constructs board

class PxConfiguration
{
public:
	PxConfiguration(const mapJson& config);
	// check if returned by copy is acceptable
	const sf::Texture* backgroundTexture(size_t index) const;
	const sf::Texture* foregroundTexture(size_t index) const;
	size_t boardStartX() const;
	size_t boardStartY() const;
	size_t boardSize() const;
	size_t fieldSize() const;
	size_t figureSize() const;
	size_t figureColorCount() const;

private:
	const sf::Texture* createTextureFromFile(const std::string& path) const;

	std::string resourceFolder;
	mapJson configJson;
	std::vector<std::string> backgroundImgSrc;
	std::vector<std::string> foregroundImgSrc;

};





