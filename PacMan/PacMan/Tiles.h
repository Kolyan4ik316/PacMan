#ifndef TILES_H
#define TILES_H
#include "EntryHeader.h"
class Tiles
{
public:
	Tiles(HGE* hge_in)
		:
	hge(hge_in)
	{
		
	}
	virtual void SetPosition(const hgeVector& pos_in)
	{
		pos = pos_in;
	};
	virtual void Update(const float& dt)
	{
		rect.Set(pos.x, pos.y, pos.x + 30.0f, pos.y + 30.0f);
	}
	virtual void Render()
	{
		hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y1);
		hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x1, rect.y2);
		hge->Gfx_RenderLine(rect.x1, rect.y2, rect.x2, rect.y2);
		hge->Gfx_RenderLine(rect.x2, rect.y1, rect.x2, rect.y2);
	}
	virtual const hgeVector GetPosition() const
	{
		return pos;
	};
	virtual ~Tiles(){};
private:
	hgeRect rect;
	HGE* hge;
	hgeVector pos;
};
#endif