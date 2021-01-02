#ifndef GHOST_H
#define GHOST_H
#include "DynamicEntity.h"
class Ghost : public DynamicEntity
{
public:
	Ghost(HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override{};
	virtual void Render(const float& sizeX, const float& sizeY) override;
	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual void MoveTo(const hgeVector& pos_in, const float& dt);
	virtual ~Ghost();
private:
	unsigned int currAnim;
	unsigned int prevAnim;
};
#endif