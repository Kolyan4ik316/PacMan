#include "Ghost.h"
Ghost::Ghost(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 50.0f;
	LoadResources();
	angle = 0.0f;
	animation.back()->Play();
	currAnim = GhostAnimation::LeftRight;
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
	animation.push_back(new hgeAnimation(tex, 2, 6, 70, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
}
void Ghost::ChoseAnimation()
{
	if(std::abs(dest.x) > std::abs(dest.y))
	{
		currAnim = GhostAnimation::LeftRight;
	}
	else
	{
		if(dest.y > 0.0f)
		{
			currAnim = GhostAnimation::Top;
		}
		else
		{
			currAnim = GhostAnimation::Bottom;
		}
	}
	if(prevAnim != currAnim)
	{
		animation.at(unsigned int(prevAnim))->Stop();
		animation.at(unsigned int(currAnim))->Play();
	}
}
void Ghost::MoveTo(const hgeVector& pos_in, const float& dt)
{
	dest.x = std::abs(pos.x) - std::abs(pos_in.x);
	dest.y =  std::abs(pos.y) - std::abs(pos_in.y);
	ChoseAnimation();
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
		pos.y -= speed * dt;
	}
	
}
void Ghost::Update(const float& dt)
{
	rect.Set(pos.x, pos.y, pos.x+30.0f, pos.y + 30.0f);
	animation.at(unsigned int(currAnim))->Update(dt);
	prevAnim = currAnim;
}
void Ghost::Render(const float& sizeX, const float& sizeY)
{
	animation.at(unsigned int(currAnim))->RenderEx(pos.x, pos.y, angle, sizeX * 2.0f, sizeY * 2.0f);
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