#ifndef GHSTARTPOINT_H
#define GHSTARTPOINT_H
#include "Entity.h"
class GHStartPoint : public Entity
{
	GHStartPoint(HGE* hge_in)
		:
	Entity(hge_in)
	{}
	virtual void Update(const float& dt) override
	{
		rect.Set(pos.x - (12.0f* scaleX) , pos.y - (12.0f* scaleY) , pos.x +(12.0f * scaleX) , pos.y +( 12.0f * scaleY));
	}
	virtual void Render() override
	{
	}

	virtual ~GHStartPoint()
	{

	}
};
#endif