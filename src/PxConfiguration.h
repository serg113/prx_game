#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// config comes from server in json format
// app reads json and constructs board

//std::string configString = "{"
//				"boardSize:7,"
//				"moveCount:5,"
//				"objectives:[{red:10,green:12,blue:20}]"
//				"figureColorCount:5"
//			"}";

// issue 1, choose json library to parse config string 

typedef std::map<std::string, int> mapJson;

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





