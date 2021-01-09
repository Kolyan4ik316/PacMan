#ifndef PACMAN_H
#define PACMAN_H
#include "Ghost.h"

class PacMan : public DynamicEntity
{
public:
	PacMan(HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	//virtual void Render(const float& sizeX, const float& sizeY) override;
	virtual void ChoseAnimation() override{};
	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual ~PacMan();
private:


};
#endif