#ifndef ENTITY_H
#define ENTITY_H
#include "EntryHeader.h"
#include "Tiles.h"
class Entity
{
public:
	Entity(HGE* hge_in)
		:
	hge(hge_in)
	{
		sprite = NULL;
		tex = NULL;

	};
	//Update
	virtual void Update(const float& dt) = 0;
	//Render
	virtual void Render() = 0;
	//virtual void Render(const float& sizeX, const float& sizeY) = 0;
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
	virtual const hgeVector GetWorldPosition() const
	{
		return pos;
	};
	virtual const bool IsColiding(hgeRect* rect_in) const
	{
		return rect.Intersect(rect_in);
	}
	virtual hgeRect* Rectangle()
	{
		return &rect;
	}
	virtual void SetSize(const float& sizeX, const float& sizeY)
	{
		scaleX = sizeX;
		scaleY = sizeY;
	}
	virtual void SetPosTile(const hgeVector& pos_in)
	{
		pos_tile = pos_in;
	}
	const hgeVector GetPosTile() const
	{
		return pos_tile;
	}
	virtual const hgeVector GetPosTile()
	{
		return pos_tile;
	}
	// Loading and releasing resources
	virtual void LoadResources() = 0;
	virtual void FreeResources() = 0;
	virtual ~Entity()
	{
		sprite = NULL;
		tex = NULL;
	};
protected:
	HGE* hge;
	// Position and direction
	hgeVector pos;
	hgeVector dir;
	hgeVector pos_tile;
	hgeSprite* sprite;
	HTEXTURE	 tex;
	hgeRect rect;
	static float scaleX;
	static float scaleY;
};



#endif