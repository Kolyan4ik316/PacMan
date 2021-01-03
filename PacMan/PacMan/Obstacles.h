#ifndef OBSTACLES_H
#define OBSTACLES_H
#include "Entity.h"
class Obstacles : public Entity
{
public:
	Obstacles(HGE* hge_in);
	virtual void LoadResources() override{};
	virtual void FreeResources() override{};
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render();
	virtual void Render(const float& sizeX, const float& sizeY){};
	virtual ~Obstacles();
};
#endif