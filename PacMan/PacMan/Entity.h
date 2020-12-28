#ifndef ENTITY_H
#define ENTITY_H
#include "EntryHeader.h"
class Entity
{
public:
	Entity(){};
	//Update
	virtual void Update(HGE *hge, const float& dt) = 0;
	//Render
	virtual void Render(HGE *hge) = 0;
	// Changing position
	virtual void SetPosition(const hgeVector& pos_in)
	{
		pos = pos_in;
	};
	// Changing direction
	virtual void SetDirection(const hgeVector& dir_in)
	{
		dir = dir_in;
	};
	// Taking position
	virtual const hgeVector GetPosition() const
	{
		return pos;
	};
	// Loading and releasing resources
	virtual void LoadResources(HGE *hge) = 0;
	virtual void FreeResources(HGE *hge) = 0;
	virtual ~Entity(){};
protected:
	// Position and direction
	hgeVector pos;
	hgeVector dir;
};



#endif