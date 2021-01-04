#include "DynamicEntity.h"
float Entity::scaleX = 1.0f;
float Entity::scaleY = 1.0f;
DynamicEntity::DynamicEntity(HGE *hge_in)
	:
	Entity(hge_in)
{
	speed = 0.0f;
}
DynamicEntity::~DynamicEntity()
{
	while(!animation.empty())
	{
		delete animation.back();
		animation.pop_back();
	}
}