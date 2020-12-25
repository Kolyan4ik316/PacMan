#ifndef ENTITY_H
#define ENTITY_H
#include "EntryHeader.h"
class Entity
{
public:
	Entity(){};
	//Update
	virtual void Update(const float dt) = 0;
	//Render
	virtual void Render(HGE *hge) = 0;
	virtual ~Entity(){};
protected:
	static position pos;
}


#endif