#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H
#include "Entity.h"
class DynamicEntity : public Entity
{
public:
	DynamicEntity(HGE* hge_in);
	virtual void ChoseAnimation() = 0;
	virtual ~DynamicEntity();
protected:
	float speed;
	std::vector<hgeAnimation*> animation;
	float angle;
private:

};
#endif