#ifndef PACMAN_H
#define PACMAN_H
#include "Entity.h"

class PacMan : public Entity
{
public:
	PacMan(HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	virtual void Render(const float& sizeX, const float& sizeY) override;
	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual ~PacMan();
protected:
	/*void boom(HGE* hge) 
	{
		int pan=int((x-400)/4);
		//float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
		hge->Effect_PlayEx(snd,100,pan,pitch);
	};*/
protected:
	float speed;

};
#endif