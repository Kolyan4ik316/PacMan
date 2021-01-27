#include "DynamicEntity.h"
float Entity::scaleX = 1.0f;
float Entity::scaleY = 1.0f;
DynamicEntity::DynamicEntity(HGE *hge_in)
	:
	Entity(hge_in)
{
	speed = 0.0f;
	canSolve = 0.0f;
	givenTimeForSolving = 0.5f;
}
bool DynamicEntity::TimeForSolvingWasReached()
{
	return canSolve >= givenTimeForSolving;
}
void DynamicEntity::SetSpeed(const float& speed_in)
{
	speed = speed_in;
}
void DynamicEntity::ResetTimeForSolving()
{
	canSolve = 0.0f;
}
void DynamicEntity::SetStartPoint(Tiles* tile)
{
	startPoint = tile;
}
void DynamicEntity::SetGloabalGoal(const hgeVector gloabalGoal_in)
{
	gloabalGoal = gloabalGoal_in;
}
void DynamicEntity::SetGloabalStart(const hgeVector gloabalStart_in)
{
	gloabalStart = gloabalStart_in;
}
const hgeVector DynamicEntity::GetTileGoal() const
{
	return gloabalGoal;
}
Tiles* DynamicEntity::GetStartPoint()
{
	return startPoint;
}
DynamicEntity::~DynamicEntity()
{
	while(!animation.empty())
	{
		delete animation.back();
		animation.pop_back();
	}
}