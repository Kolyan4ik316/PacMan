#ifndef TILES_H
#define TILES_H
#include "EntryHeader.h"
class Tiles
{
public:
	Tiles(HGE* hge_in, const hgeVector& pos_in)
		:
	hge(hge_in),
	pos(pos_in)
	{
		haveObstacles = false;
		float posX = originX / scaleX - 400.0f + (36.0f * pos.x);
		float posY = originY / scaleY - 300.0f + (36.0f * pos.y);
		worldPos = hgeVector(posX, posY);
		rect.Set(worldPos.x * scaleX, worldPos.y * scaleY, (worldPos.x + 36.0f) * scaleX, (worldPos.y + 36.0f) * scaleY);
		
	}
	virtual void SetPosition(const hgeVector& pos_in)
	{
		pos = pos_in;
	};
	const hgeVector GetWorldPos() const 
	{
		return worldPos;
	};
	virtual void SetTargetPosition(const hgeVector& pos_in)
	{
		targetPos = pos_in;
	};
	virtual void Update(const float& dt)
	{
		//rect.Set(worldPos.x * scaleX, worldPos.y * scaleY, (worldPos.x + 36.0f) * scaleX, (worldPos.y + 36.0f) * scaleY);
	}
	virtual void Render()
	{
		hgeColor* color;
		//color = &hgeColor(255.0f, 0.0f, 255.0f, 0.0f);
	

		color = &hgeColor(155.0f, 0.0f, 155.0f, 0.0f);

		const hgeU32 tempColor = color->GetHWColor();
		hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y1, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x1, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y2, rect.x2, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x2, rect.y1, rect.x2, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y1, GetOrigin().x, GetOrigin().y, tempColor);
	}
	virtual void RenderChosen()
	{
		hgeColor* color;
		color = &hgeColor(255.0f, 0.0f, 255.0f, 0.0f);
		const hgeU32 tempColor = color->GetHWColor();
		hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y1, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x1, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y2, rect.x2, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x2, rect.y1, rect.x2, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y1, GetOrigin().x, GetOrigin().y, tempColor);
	}
	virtual const hgeVector GetPosition() const
	{
		return pos;
	};
	virtual const hgeVector GetOrigin()const
	{
		return hgeVector((rect.x2 + rect.x1)/ 2.0f, (rect.y2 + rect.y1) / 2.0f);
	}
	virtual const bool IsInside(const hgeVector& pos_in) const
	{
		return rect.TestPoint(pos_in.x, pos_in.y); 
	}
	virtual void HaveObstacles(const bool& doHave)
	{
		haveObstacles = doHave;
	}
	virtual const bool ObstaclesInside() const
	{
		return haveObstacles;
	}
	virtual ~Tiles(){};
public:
	static void SetScale(const float& scaleX_in, const float& scaleY_in)
	{
		scaleX = scaleX_in;
		scaleY = scaleY_in;
	}
	static void SetOrigin(const float& originX_in, const float& originY_in)
	{
		originX = originX_in;
		originY = originY_in;
	}
private:
	hgeVector worldPos;
	hgeRect rect;
	HGE* hge;
	bool haveObstacles;
	static float scaleX;
	static float scaleY;
	static float originX;
	static float originY;
public:
	hgeVector pos;
	hgeVector targetPos;

};
#endif