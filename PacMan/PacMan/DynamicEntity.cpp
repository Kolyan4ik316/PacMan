#include "DynamicEntity.h"
DynamicEntity::DynamicEntity(HGE *hge_in)
	:
	Entity(hge_in)
{
	tex = NULL;
	sprite = NULL;
	snd = NULL;
	animation = NULL;
	speed = 0.0f;
}
DynamicEntity::~DynamicEntity()
{

}