#ifndef PMSTARTPOINT_H
#define PMSTARTPOINT_H
#include "Entity.h"
class PMStartPoint : public Entity
{
public:
	PMStartPoint(HGE* hge_in)
		:
	Entity(hge_in)
	{}
	virtual void Update(const float& dt) override
	{
		rect.Set(pos.x - (12.0f* scaleX) , pos.y - (12.0f* scaleY) , pos.x +(12.0f * scaleX) , pos.y +( 12.0f * scaleY));
	}
	virtual void LoadResources() override
	{
	}
	virtual void FreeResources() override
	{
	}
	virtual void Render() override
	{
	}

	virtual ~PMStartPoint()
	{

	}
};
#endif