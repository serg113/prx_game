#pragma once

// need to be renemed to EngineBase.h

class PxEngineBase
{
	virtual ~PxEngineBase() = default;
};

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

struct PxPos;
struct PxFieldPoint;

typedef std::vector<PxFieldPoint>(*PatternCB_t)(std::map<PxPos, PxFieldPoint>, PxFieldPoint);
typedef void(*ActOnSuccessCB_t)(IPatternMatchable2D* engine, std::vector<PxFieldPoint>);
typedef void(*ActOnFailCB_t)(IResettableEngine* engine);
