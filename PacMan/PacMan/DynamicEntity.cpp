#include "DynamicEntity.h"
DynamicEntity::DynamicEntity(HGE *hge_in)
	:
	Entity(hge_in)
{
	animation = NULL;
	speed = 0.0f;
}
DynamicEntity::~DynamicEntity()
{
	animation = NULL;
}