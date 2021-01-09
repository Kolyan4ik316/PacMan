#ifndef GHOST_H
#define GHOST_H
#include "DynamicEntity.h"
class Ghost : public DynamicEntity
{
public:
	Ghost(HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	virtual void Render(const float& sizeX, const float& sizeY) override;
	virtual void RenderLineToGoal();
	virtual void ChoseAnimation() override;
	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual void SetDestination(const hgeVector& pos_in);
	virtual ~Ghost();
protected:
	enum GhostAnimation : unsigned int
	{
		LeftRight,
		Top,
		Bottom
	};
	GhostAnimation currAnim;
	GhostAnimation prevAnim;
	hgeVector destination;
	hgeVector goal;
public:
	std::list<Tiles*> listToVisit;
	Tiles* nodeStart;
	Tiles* nodeEnd;
	Tiles* prevNodeEnd;
	float canSolve;
};
#endif