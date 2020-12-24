#ifndef ENTITY_H
#define ENTITY_H
#include "EntryHeader.h"
class Entity
{
public:
	Entity(){};
	//Update
	virtual bool Update() = 0;
	//Render
	virtual bool Render() = 0;
	virtual ~Entity(){};
}


#endif