#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H
#include "Entity.h"
class DynamicEntity : public Entity
{
public:
	DynamicEntity(HGE* hge_in);
	virtual void ChoseAnimation() = 0;
	virtual ~DynamicEntity();
	virtual bool TimeForSolvingWasReached();
	virtual void ResetTimeForSolving();
	float givenTimeForSolving;
protected:
	float speed;
	std::vector<hgeAnimation*> animation;
	float angle;
	hgeVector destination;
	hgeVector goal;
	float canSolve;
public:
	Tiles* nodeStart;
	Tiles* nodeEnd;

};
#endif