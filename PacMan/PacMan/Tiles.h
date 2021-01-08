#ifndef TILES_H
#define TILES_H
#include "EntryHeader.h"
class Tiles
{
public:
	Tiles(HGE* hge_in, const hgeVector& pos_in, float scaleX_in, float scaleY_in)
		:
	hge(hge_in),
	pos(pos_in),
	scaleX(scaleX_in),
	scaleY(scaleY_in)
	{
		haveObstacles = false;
		haveGoal = false;
		rect.Set(pos.x * scaleX, pos.y * scaleY, (pos.x + 36.0f) * scaleX, (pos.y + 36.0f) * scaleY);
		bVisited = false;
	}
	virtual void SetPosition(const hgeVector& pos_in)
	{
		pos = pos_in;
	};
	virtual void Update(const float& dt)
	{
		rect.Set(pos.x * scaleX, pos.y * scaleY, (pos.x + 36.0f) * scaleX, (pos.y + 36.0f) * scaleY);
	}
	virtual void Render()
	{
		hgeColor color(255.0f, 0.0f, 255.0f, 0.0f);
		const hgeU32 tempColor = color.GetHWColor();
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
	virtual void HaveGoal(const bool& doHave)
	{
		haveGoal = doHave;
	}
	virtual const bool GoalInside() const
	{
		return haveGoal;
	}
	/*virtual void Render(const float& sizeX, const float& sizeY)
	{
		hgeColor color(255.0f, 0.0f, 255.0f, 0.0f);
		const hgeU32 tempColor = color.GetHWColor();
		float offset = 3.0f;
		for(float i = 0.0f; i < offset; i++)
		{
			hge->Gfx_RenderLine(rect.x1 * sizeX, (rect.y1 + i) * sizeY, rect.x2 * sizeX, (rect.y1 + i) * sizeY, tempColor);
			hge->Gfx_RenderLine((rect.x1 + i) * sizeX, rect.y1 * sizeY, (rect.x1 + i) * sizeX, rect.y2 * sizeY, tempColor);
			hge->Gfx_RenderLine(rect.x1 * sizeX, (rect.y2 - i) * sizeY, rect.x2 * sizeX, (rect.y2 - i) * sizeY, tempColor);
			hge->Gfx_RenderLine((rect.x2 - i) * sizeX, rect.y1 * sizeY, (rect.x2 - i) * sizeX, rect.y2 * sizeY, tempColor);
		}
	}*/
	virtual ~Tiles(){};
private:
	hgeRect rect;
	HGE* hge;
	bool haveObstacles;
	float scaleX;
	float scaleY;
	bool haveGoal;
public:
	float fGlobalGoal;				// Distance to goal so far
	float fLocalGoal;
	hgeVector pos;
	bool bVisited;			// Have we searched this node before?
	std::vector<Tiles*> vecNeighbours;	// Connections to neighbours
	Tiles* parent;					// Node connecting to this node that offers shortest parent
};
#endif