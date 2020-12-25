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
	virtual void SetPosition(const float& x, const float& y)
	{
		pos_x = x;
		pos_y = y;
	};
	virtual void Render(HGE *hge) = 0;
	virtual void LoadResources(HGE *hge) = 0;
	virtual void FreeResources(HGE *hge) = 0;
	virtual ~Entity(){};
protected:
	static float pos_x;
	static float pos_y;
};


#endif