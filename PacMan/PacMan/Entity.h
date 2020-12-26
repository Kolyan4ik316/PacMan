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
	virtual const float GetPositionX() const
	{
		return pos_x;
	};
	virtual void SetDirection(const float& dirX, const float& dirY)
	{
		dir_x = dirX;
		dir_y = dirY;
	};
	virtual const float GetPositionY() const
	{
		return pos_y;
	};
	virtual void Render(HGE *hge) = 0;
	virtual void LoadResources(HGE *hge) = 0;
	virtual void FreeResources(HGE *hge) = 0;
	virtual ~Entity(){};
protected:

	static float pos_x;
	static float pos_y;
	static float dir_x;
	static float dir_y;
};



#endif