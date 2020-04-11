#pragma once


class IResettableEngine
{
public:
	virtual void resetMovement() = 0;
};

class IPatternMatchable2D
{
public:
	virtual void matchThreeInSequenceDirectionX() = 0;
	virtual void matchThreeInSequenceDirectoryY() = 0;
	virtual void matchFourInSquare() = 0;
	virtual void matchTypeT() = 0;
};