#ifndef PACMAN_H
#define PACMAN_H
#include "Entity.h"

class PacMan : public Entity
{
public:
	PacMan();
	//Update
	virtual void Update(HGE *hge, const float dt) override;
	//Render
	virtual void Render(HGE *hge) override;
	virtual void LoadResources(HGE *hge) override;
	virtual void FreeResources(HGE *hge) override;
	virtual ~PacMan();
protected:
	static hgeSprite* sprite;
	static HTEXTURE	 tex;
};
#endif