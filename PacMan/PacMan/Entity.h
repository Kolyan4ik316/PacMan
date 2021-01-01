#ifndef ENTITY_H
#define ENTITY_H
#include "EntryHeader.h"
class Entity
{
public:
	Entity(HGE* hge_in)
		:
	hge(hge_in)
	{};
	//Update
	virtual void Update(const float& dt) = 0;
	//Render
	virtual void Render() = 0;
	virtual void Render(const float& sizeX, const float& sizeY) = 0;
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
	virtual void LoadResources() = 0;
	virtual void FreeResources() = 0;
	virtual ~Entity(){};
protected:
	HGE* hge;
	// Position and direction
	hgeVector pos;
	hgeVector dir;
	hgeSprite* sprite;
	HTEXTURE	 tex;
	HEFFECT snd;
};



#endif