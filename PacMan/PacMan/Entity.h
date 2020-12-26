#ifndef ENTITY_H
#define ENTITY_H
#include "EntryHeader.h"
class Entity
{
public:
	Entity(){};
	//Update
	virtual void Update(HGE *hge, const float dt) = 0;
	//Render
	virtual void SetPosition(const hgeVector& pos_in)
	{
		pos = pos_in;
	};
	virtual void SetDirection(const hgeVector& dir_in)
	{
		dir = dir_in;
	};
	virtual const hgeVector GetPosition() const
	{
		return pos;
	};
	virtual void Render(HGE *hge) = 0;
	virtual void LoadResources(HGE *hge) = 0;
	virtual void FreeResources(HGE *hge) = 0;
	virtual ~Entity(){};
protected:
	static hgeVector pos;
	static hgeVector dir;
};



#endif