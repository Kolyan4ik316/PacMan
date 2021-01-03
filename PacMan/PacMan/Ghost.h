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
	virtual void ChoseAnimation() override;
	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual void MoveTo(const hgeVector& pos_in, const float& dt);
	virtual ~Ghost();
protected:
	enum GhostAnimation : unsigned int
	{
		LeftRight,
		Top,
		Bottom
	};
	GhostAnimation currAnim;
	GhostAnimation prevAnim;
private:
	hgeVector dest;
};
#endif