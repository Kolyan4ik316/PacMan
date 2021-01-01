#include "Ghost.h"
Ghost::Ghost(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 50.0f;
	LoadResources();
	angle = 0.0f;
	animation.back()->Play();
}
void Ghost::LoadResources()
{
	tex=hge->Texture_Load("pacman.png");
	if(!tex)
	{
		throw(std::exception("Can't find pacman.png"));
	}
	animation.push_back(new hgeAnimation(tex, 2, 6, 2, 17, 16, 16)); 
	//sprite = new hgeSprite(tex, 2, 2, 14, 14);
	//sprite=new hgeSprite(tex, 96, 64, 32, 32);
	//animation->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	animation.back()->SetHotSpot(7,7);
}
void Ghost::MoveTo(const hgeVector& pos_in, const float& dt)
{
	if(pos.x < pos_in.x)
	{
		pos.x += speed * dt;
	}
	if(pos.x > pos_in.x)
	{
		pos.x -= speed * dt;
	}
	if(pos.y < pos_in.y)
	{
		pos.y += speed * dt;
	}
	if(pos.y > pos_in.y)
	{
		pos.y -= speed * dt;
	}
	
}
void Ghost::Update(const float& dt)
{
	animation.back()->Update(dt);
}
void Ghost::Render(const float& sizeX, const float& sizeY)
{
	animation.back()->RenderEx(pos.x, pos.y, angle, sizeX * 2.0f, sizeY * 2.0f);
}
void Ghost::FreeResources()
{
	hge->Texture_Free(tex);
}
Ghost::~Ghost()
{
	FreeResources();
	while(!animation.empty())
	{
		delete animation.back();
		animation.pop_back();
	}
}