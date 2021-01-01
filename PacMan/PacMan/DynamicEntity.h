#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H
#include "Entity.h"
class DynamicEntity : public Entity
{
public:
	DynamicEntity(HGE* hge_in);

	virtual ~DynamicEntity();
protected:
	float speed;
	hgeAnimation* animation;
	float angle;
private:

};
#endif