#pragma once

#include "PxGame.h"
#include "PxConfiguration.h"
#include <SFML/Graphics.hpp>

#include <set>

struct PxField
{
	sf::Sprite* back;
	sf::Sprite* front;
	bool isFrontVisible = true;
	bool isChecked = false;
	int frontIndex;
	const sf::Texture* tempTxt;
};

struct PxScore
{
	sf::Sprite* figure;
	sf::Text* text;
	size_t score;
	size_t objective;
	int figureIndex;
};

class UnInitializedGame
{
public:
	virtual InitializedGame* init() = 0;
};

class PxMatchGame final: UnInitializedGame, InitializedGame
{
public:
	PxMatchGame(const PxConfiguration options);
	InitializedGame* init() override;
	InitializedGame* draw(sf::RenderTarget* app) override;
	InitializedGame* touch(int x, int y) override;

private:

	void initGameMap();
	void initGameHeader();

	void drawFields(sf::RenderTarget* app);
	void drawHeader(sf::RenderTarget* app);

	void dropDownFigures(size_t index);
	void swapAndMatch(size_t lhsIndex, size_t rhsIndex);
	void swapFigures(size_t lhsIndex, size_t rhsIndex);

	bool patternIsMatched(size_t index) const;
	bool positionIsOnBoard(int x, int y) const;

	size_t positionToIndex(int x, int y) const;
	bool indexIsValid(size_t index) const;
	size_t randomIndexInRange(size_t max) const;

	std::set<size_t> matchThreeXY(size_t index) const;
	void actionOnMatchingThreeXY(const std::set<size_t>& indices);

	void checkField(size_t index);
	void unCheckField(size_t index);
	bool fieldIsChecked(size_t index) const;

	sf::Text* createText(float X, float Y, const std::string& text) const;
	sf::Sprite* createBack(float X, float Y, size_t index) const;
	sf::Sprite* createFront(float X, float Y, size_t index) const;

	float frontOffset() const;
	size_t fieldsDistance(size_t lhsIndex, size_t rhsIndex) const;
	size_t fieldRow(size_t index) const;
	size_t fieldColumn(size_t index) const;
	int addRow(size_t index) const;
	int addColumn(size_t index) const;
	int subtractRow(size_t index) const;
	int subtractColumn(size_t index) const;

	PxConfiguration opt;
	std::vector<PxField> fields;
	std::vector<PxScore> scores;

	size_t currentIndex;

	
};