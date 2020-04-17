#pragma once

#include "PxConfiguration.h"
#include "PxPatternInterface.h"

#include <set>

//------- external interface ---------

class InitializedGame
{
public:
	virtual InitializedGame* draw(sf::RenderWindow* app) = 0;
	virtual InitializedGame* touch(int x, int y) = 0;
};

InitializedGame* createGame(const PxConfiguration options);

//------------------------------------

struct PxyField
{
	sf::Sprite* back;
	sf::Sprite* front;
	bool isFrontVisible = true;
	bool isChecked = false;
	int frontIndex;
	const sf::Texture* tempTxt;
};

// all below is internal functionality
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
	InitializedGame* draw(sf::RenderWindow* app) override;
	InitializedGame* touch(int x, int y) override;

private:
	void initGameMap();
	void dropDown(int index);
	void swapAndMatch(size_t lhsIndex, size_t rhsIndex);
	void swapFigures(size_t lhsIndex, size_t rhsIndex);

	bool patternIsMatched(size_t index) const;
	bool positionIsOnBoard(int x, int y) const;

	size_t positionToIndex(int x, int y) const;

	std::set<size_t> matchThreeXY(size_t index) const;
	void onMatchingThreeXY(const std::set<size_t>& indices);

	void checkField(size_t index);
	void unCheckField(size_t index);
	bool fieldIsChecked(size_t index);

	sf::Sprite* createBack(size_t X, size_t Y, size_t index) const;
	sf::Sprite* createFront(size_t X, size_t Y, size_t index) const;

	// this is another class
	size_t fieldRow(size_t index) const;
	size_t fieldColumn(size_t index) const;
	int addRow(size_t index) const;
	int addColumn(size_t index) const;
	int subtractRow(size_t index) const;
	int subtractColumn(size_t index) const;

	PxConfiguration opt;
	std::vector<PxPattern*> patterns;
	std::vector<PxyField> fields;

	size_t currentIndex;
	bool isCurrrentIndexValid = false;

};