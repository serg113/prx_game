#include "PxMatchGame.h"

#include <random>
#include <iostream>
#include <assert.h> 


PxMatchGame::PxMatchGame(const PxConfiguration options) : opt(options){ };

InitializedGame* PxMatchGame::init()
{
	initGameHeader();
	initGameMap();
	std::cout << "initial game map initialized" << std::endl;
	return this;
}

InitializedGame* PxMatchGame::draw(sf::RenderTarget* app)
{
	drawHeader(app);
	drawFields(app);
	
	return this;
}

InitializedGame* PxMatchGame::touch(int x, int y)
{
	size_t index = positionToIndex(x, y);

	if (indexIsValid(index))
	{
		if (fieldIsChecked(currentIndex)) 
		{
			unCheckField(currentIndex);
			swapAndMatch(currentIndex, index);
		} 
		else {
			checkField(index);
		}
	} 
	else {
		unCheckField(currentIndex);
	}
	return this;
}

void PxMatchGame::initGameMap()
{
	for (size_t i = 0; i < opt.boardSize(); ++i)
	{
		for (size_t j = 0; j < opt.boardSize(); ++j)
		{
			size_t posX = opt.boardStartX() + opt.fieldSize() * i; // column
			size_t posY = opt.boardStartY() + opt.fieldSize() * j; // row

			PxField field;
			field.back = createBack(posX, posY, (i + j) % 2);

			while (true)
			{
				int textureIndex = randomIndexInRange(opt.figureColorCount());

				field.front = createFront(posX + frontOffset(), posY + frontOffset(), textureIndex);

				field.frontIndex = textureIndex;

				fields.push_back(field);

				if (patternIsMatched(fields.size()-1))
					fields.pop_back();
				else break;
			}
		}
	}
}

void PxMatchGame::initGameHeader()
{
	for (size_t i = 0; i < opt.objectiveCount(); ++i)
	{
		// messy part
		PxScore score;
		score.figure = createFront(100 + i*(100 + opt.figureSize()), 20 , i);
		score.figureIndex = i;
		score.objective = opt.objective(i);
		score.score = 0;

		std::string text = "0/" + std::to_string(opt.objective(i));
		score.text = createText(180 + i * (100 + opt.figureSize()), 20, text);

		scores.push_back(score);
	}
}

void PxMatchGame::drawFields(sf::RenderTarget* app)
{
	auto field = fields.begin();

	do {
		app->draw(*field->back); // can be drown only once ?!

		if (field->isFrontVisible)
		{
			app->draw(*field->front);
		}
		else
		{
			size_t fieldIndex = field - fields.begin();

			dropDownFigures(fieldIndex);

			auto indices = matchThreeXY(fieldIndex);

			actionOnMatchingThreeXY(indices);
		}
	} while (++field != fields.end());
}

void PxMatchGame::drawHeader(sf::RenderTarget* app)
{
	for (auto header : scores)
	{
		app->draw(*header.figure);
		app->draw(*header.text);
	}
}


void PxMatchGame::dropDownFigures(size_t index)
{
	if (fieldRow(index) > 0)
	{
		swapFigures(index, index - 1);
	}
	else
	{
		int textureIndex = randomIndexInRange(opt.figureColorCount());

		fields[index].front->setTexture(*opt.foregroundTexture(textureIndex), true);

		fields[index].frontIndex = textureIndex;

		fields[index].isFrontVisible = true;
	}
}

void PxMatchGame::swapAndMatch(size_t lhsIndex, size_t rhsIndex)
{
	if (fieldsDistance(lhsIndex, rhsIndex) != 1)
		return;

	swapFigures(lhsIndex, rhsIndex);

	auto fields = matchThreeXY(lhsIndex);
	auto fields2 = matchThreeXY(rhsIndex);

	fields.insert(fields2.begin(), fields2.end());

	if (fields.size())
		actionOnMatchingThreeXY(fields);
	else
		swapFigures(lhsIndex, rhsIndex);
}


void PxMatchGame::swapFigures(size_t lhs, size_t rhs)
{	
	if (!indexIsValid(lhs) || !indexIsValid(rhs)) return;

	PxField temp;
	
	temp.tempTxt = fields[lhs].front->getTexture();
	temp.isFrontVisible = fields[lhs].isFrontVisible;
	temp.frontIndex = fields[lhs].frontIndex;

	fields[lhs].front->setTexture(*fields[rhs].front->getTexture(), true);
	fields[lhs].isFrontVisible = fields[rhs].isFrontVisible;
	fields[lhs].frontIndex = fields[rhs].frontIndex;

	fields[rhs].front->setTexture(*temp.tempTxt, true);
	fields[rhs].isFrontVisible = temp.isFrontVisible;
	fields[rhs].frontIndex = temp.frontIndex;
}

bool PxMatchGame::patternIsMatched(size_t index) const
{
	return matchThreeXY(index).size() > 0;
}


bool PxMatchGame::positionIsOnBoard(int x, int y) const
{
	if (x > opt.boardStartX()
		&& y > opt.boardStartY()
		&& x < (opt.boardSize() * opt.fieldSize() + opt.boardStartX())
		&& y < (opt.boardSize() * opt.fieldSize() + opt.boardStartY()))
		return true;
	return false;
}

size_t PxMatchGame::positionToIndex(int x, int y) const
{
	size_t index;

	if (positionIsOnBoard(x, y))
	{
		size_t column = static_cast<size_t>((x - opt.boardStartX()) / opt.fieldSize());
		size_t row = static_cast<size_t>((y - opt.boardStartY()) / opt.fieldSize());

		index = column * opt.boardSize() + row;
	
		std::cout << "row: " << row << " column: " << column << std::endl;
	}
	else
	{
		index = fields.size();
	}

	return index;
}

bool PxMatchGame::indexIsValid(size_t index) const
{
	return index < fields.size();
}

size_t PxMatchGame::randomIndexInRange(size_t max) const
{
	std::random_device rd;

	return static_cast<size_t>(rd() % max);
}


std::set<size_t> PxMatchGame::matchThreeXY(size_t index) const
{
	if (!indexIsValid(index)) return {};

	std::set<size_t> matchPoints;

	auto txtIndex = fields[index].frontIndex;

	int ind = addColumn(index);

	if (ind >= 0 && fields[ind].frontIndex == txtIndex)
	{
		if (addColumn(ind) >= 0 && fields[addColumn(ind)].frontIndex == txtIndex)
			matchPoints.insert({ static_cast<size_t>(ind), static_cast<size_t>(addColumn(ind)) });

		else if(subtractColumn(index) >= 0 && fields[subtractColumn(index)].frontIndex == txtIndex)
			matchPoints.insert({ static_cast<size_t>(ind), static_cast<size_t>(subtractColumn(index)) });
	}

	ind = subtractColumn(index);

	if(ind >= 0 && subtractColumn(ind) >= 0 
		&& fields[ind].frontIndex == txtIndex && fields[subtractColumn(ind)].frontIndex == txtIndex)
		matchPoints.insert({ static_cast<size_t>(ind), static_cast<size_t>(subtractColumn(ind)) });
	

	ind = addRow(index);

	if (ind >= 0 && fields[ind].frontIndex == txtIndex)
	{
		if (addRow(ind) >= 0 && fields[addRow(ind)].frontIndex == txtIndex)
			matchPoints.insert({ static_cast<size_t>(ind), static_cast<size_t>(addRow(ind)) });

		else if (subtractRow(index) >= 0 && fields[subtractRow(index)].frontIndex == txtIndex)
			matchPoints.insert({ static_cast<size_t>(ind), static_cast<size_t>(subtractRow(index)) });
	}

	ind = subtractRow(index);

	if (ind >= 0 && subtractRow(ind) >= 0
		&& fields[ind].frontIndex == txtIndex && fields[subtractRow(ind)].frontIndex == txtIndex)
		matchPoints.insert({ static_cast<size_t>(ind), static_cast<size_t>(subtractRow(ind)) });

	if (matchPoints.size() > 0)
	{
		std::cout << "matchin points found" << std::endl;
		matchPoints.insert(index);
	}

	return matchPoints;
}


void PxMatchGame::actionOnMatchingThreeXY(const std::set<size_t>& indices)
{
	for (auto index : indices)
	{
		fields[index].isFrontVisible = false;
		
		size_t frontIndex = fields[index].frontIndex;

		if (frontIndex < opt.objectiveCount())
		{
			std::string scoreTxt = std::to_string(++scores[frontIndex].score)
				+ "/" + std::to_string(scores[frontIndex].objective);

			scores[frontIndex].text->setString(scoreTxt);
		}
	}
}


void PxMatchGame::checkField(size_t index)
{
	if (!indexIsValid(index)) return;

	fields[index].tempTxt = fields[index].back->getTexture();
	fields[index].back->setTexture(*opt.backgroundTexture(2), true);
	fields[index].isChecked = true;

	currentIndex = index;
}

void PxMatchGame::unCheckField(size_t index)
{
	if (!indexIsValid(index)) return;

	fields[index].back->setTexture(*fields[index].tempTxt, true);
	fields[index].isChecked = false;
}

/*note: returns false if index not valid*/
bool PxMatchGame::fieldIsChecked(size_t index) const
{
	if (!indexIsValid(index)) return false;

	return fields[index].isChecked;
}

sf::Text* PxMatchGame::createText(float X, float Y, const std::string& text) const
{
	sf::Text* txt = new sf::Text;

	txt->setFont(*opt.font());
	txt->setString(text);
	txt->setFillColor(sf::Color::Black);
	txt->setPosition(X, Y);

	return txt;
}

sf::Sprite* PxMatchGame::createBack(float X, float Y, size_t index) const
{
	sf::Sprite* back = new sf::Sprite(*opt.backgroundTexture(index));

	back->setPosition(X, Y);

	return back;
}

sf::Sprite* PxMatchGame::createFront(float X, float Y, size_t index) const 
{
	sf::Sprite* front = new sf::Sprite(*opt.foregroundTexture(index));

	front->setPosition(X, Y);

	return front;
}

float PxMatchGame::frontOffset() const
{
	return (opt.fieldSize() - opt.figureSize()) / 4.f;
}

size_t PxMatchGame::fieldsDistance(size_t lhsIndex, size_t rhsIndex) const
{
	size_t diff = lhsIndex > rhsIndex ? lhsIndex - rhsIndex : rhsIndex - lhsIndex;

	return (diff / opt.boardSize() + diff % opt.boardSize());
}

size_t PxMatchGame::fieldRow(size_t index) const
{
	return index % opt.boardSize();
}

size_t PxMatchGame::fieldColumn(size_t index) const
{
	return index / opt.boardSize();
}

int PxMatchGame::addRow(size_t index) const
{
	index++;

	return index >= fields.size() ? -1 : index;
}

int PxMatchGame::addColumn(size_t index) const
{
	index += opt.boardSize();

	return  index >= fields.size() ? -1 : index;
}

int PxMatchGame::subtractRow(size_t index) const
{
	index--;

	return index < 0 ? -1 : index;
}

int PxMatchGame::subtractColumn(size_t index) const
{
	index -= opt.boardSize();

	return index < 0 ? -1 : index;
}