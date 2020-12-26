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
	/*void boom(HGE* hge) 
	{
		int pan=int((x-400)/4);
		//float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
		hge->Effect_PlayEx(snd,100,pan,pitch);
	};*/
protected:
	static hgeSprite* sprite;
	static HTEXTURE	 tex;
	// Some "gameplay" variables and constants
	static const float speed;
	static HEFFECT snd;

};
#endif