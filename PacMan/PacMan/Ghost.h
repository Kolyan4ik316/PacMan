#ifndef GHOST_H
#define GHOST_H
#include "DynamicEntity.h"
#include "PathFinder.h"
class Ghost : public DynamicEntity
{
public:
	Ghost(HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	//virtual void Render(const float& sizeX, const float& sizeY) override;
	virtual void RenderLineToGoal();
	virtual void ChoseAnimation() override;
	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual void SetDestination(const hgeVector& pos_in);
	virtual void SetPathTo(const hgeVector& target);
	virtual Tiles* Ghost::GetNextPosition();
	virtual void SetPathFinder(class PathFinder* pathFinder_in);
	virtual void SwitchAtacked();
	virtual bool CanBeAtacket();
	virtual bool WasAttacked();
	virtual void SwitchWasAtacked();
	virtual ~Ghost();
	float releaseTime;
private:
	bool canBeAtacket;
	bool wasAtattacked;
protected:
	enum GhostAnimation : unsigned int
	{
		LeftRight,
		Top,
		Bottom,
		Scary,
		Attacked
	};
	GhostAnimation currAnim;
	GhostAnimation prevAnim;
	class PathFinder* pathFinder;

public:
	std::vector<Tiles*> pathToTarget;
};
#endif