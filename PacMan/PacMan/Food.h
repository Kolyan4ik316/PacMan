#ifndef FOOD_H
#define FOOD_H
#include "Entity.h"
class Food : public Entity
{
public:
	Food(HGE* hge_in)
		:
	Entity(hge_in)
	{
		isEaten = false;
		LoadResources();
	}
	virtual void LoadResources()
	{
		tex=hge->Texture_Load("pacman.png");
		if(!tex)
		{
			throw(std::exception("Can't find pacman.png"));
		}
		sprite = new hgeSprite(tex, 223, 52, 14, 14);
		sprite->SetHotSpot(8.0f,8.0f);
	}
	virtual void FreeResources()
	{
		delete sprite;
		hge->Texture_Free(tex);
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
		rect.Set(pos.x * scaleX , pos.y * scaleY , (pos.x + 8.0f) * scaleX , (pos.y + 8.0f) * scaleY);
	}
	virtual void Render() override
	{
		sprite->RenderEx(pos.x, pos.y, 0.0f, scaleX * 2.0f, scaleY * 2.0f);
	}

	virtual ~Food()
	{
		FreeResources();
	}
private:
	bool isEaten;

};
#endif