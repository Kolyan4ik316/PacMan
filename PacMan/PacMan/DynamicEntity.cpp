#include "DynamicEntity.h"
DynamicEntity::DynamicEntity(HGE *hge_in)
	:
	Entity(hge_in)
{
	speed = 0.0f;
}
DynamicEntity::~DynamicEntity()
{
}