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
	void SetStartPoint(Tiles* tile);
	void SetSpeed(const float& speed_in);
	void SetGloabalGoal(const hgeVector gloabalGoal_in);
	const hgeVector GetTileGoal() const;
	void SetGloabalStart(const hgeVector gloabalStart_in);
	Tiles* GetStartPoint();
protected:
	float speed;
	std::vector<hgeAnimation*> animation;
	float angle;
	hgeVector destination;
	hgeVector goal;
	hgeVector gloabalGoal;
	float canSolve;
public:
	

};
#endif