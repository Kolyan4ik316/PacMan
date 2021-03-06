#ifndef HOLYFOOD_H
#define HOLYFOOD_H
#include "Food.h"
class HolyFood : public Entity
{
public:
	HolyFood(HGE* hge_in)
		:
	Entity(hge_in)
	{
		isEaten = false;
		LoadResources();
	}
	virtual void LoadResources() override
	{
		tex=hge->Texture_Load("Images\\pacman.png");
		if(!tex)
		{
			throw(std::exception("Can't find Images\\pacman.png"));
		}
		animation = new hgeAnimation(tex, 2, 2, 223, 52, 16, 16);
		animation->SetHotSpot(8.0f,8.0f);
		animation->Play();
	}
	virtual void EatFood()
	{
		isEaten = true;
	}
	virtual const bool IsEaten() const
	{
		return isEaten;
	}
	virtual void Update(const float& dt) override
	{
		animation->Update(dt);
		rect.Set(pos.x - (10.0f * scaleX) , pos.y - (10.0f * scaleY) , pos.x +(10.0f * scaleX) , pos.y + (10.0f * scaleY));
	}
	virtual void Render() override
	{
		animation->RenderEx(pos.x, pos.y, 0.0f, scaleX * 2.0f, scaleY * 2.0f);
		//hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y2);
	}
	virtual void FreeResources() override
	{
		hge->Texture_Free(tex);
	}
	virtual ~HolyFood()
	{
		FreeResources();
		delete animation;
	}
private:
	hgeAnimation* animation;
	bool isEaten;
};
#endif