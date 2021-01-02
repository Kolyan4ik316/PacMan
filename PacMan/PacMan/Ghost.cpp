#include "Ghost.h"
Ghost::Ghost(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 50.0f;
	LoadResources();
	angle = 0.0f;
	animation.back()->Play();
	currAnim = 1;
	prevAnim = currAnim;
}
void Ghost::LoadResources()
{
	tex=hge->Texture_Load("pacman.png");
	if(!tex)
	{
		throw(std::exception("Can't find pacman.png"));
	}
	animation.push_back(new hgeAnimation(tex, 2, 6, 2, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
	animation.push_back(new hgeAnimation(tex, 2, 6, 35, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
}
void Ghost::MoveTo(const hgeVector& pos_in, const float& dt)
{
	hgeVector dest;
	dest.x = std::abs(pos_in.x) - std::abs(pos.x);
	dest.y = std::abs(pos_in.y) - std::abs(pos.y);
	if(std::abs(dest.x) > std::abs(dest.y))
	{
		currAnim = 0;
	}
	else
	{
		currAnim = 1;
	}
	if(pos.x < pos_in.x)
	{
		animation.at(0)->SetFlip(true, false, true);	
		pos.x += speed * dt;
	}
	if(pos.x > pos_in.x)
	{
		animation.at(0)->SetFlip(false, false, true);
		pos.x -= speed * dt;
	}
	if(pos.y < pos_in.y)
	{
		pos.y += speed * dt;
	}
	if(pos.y > pos_in.y)
	{
		//currAnim = 1;
		pos.y -= speed * dt;
	}
	
}
void Ghost::Update(const float& dt)
{
	if(prevAnim != currAnim)
	{
		animation.at(prevAnim)->Stop();
		animation.at(currAnim)->Play();
	}
	animation.at(currAnim)->Update(dt);
	prevAnim = currAnim;
}
void Ghost::Render(const float& sizeX, const float& sizeY)
{
	animation.at(currAnim)->RenderEx(pos.x, pos.y, angle, sizeX * 2.0f, sizeY * 2.0f);
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