#include "PacMan.h"
//hgeSprite* PacMan::sprite = 0;
//HTEXTURE PacMan::tex = 0;
//HEFFECT PacMan::snd = 0;
//const float PacMan::speed = 90;
//const float PacMan::friction = 0.98f;
PacMan::PacMan(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 90.0f;
	LoadResources();
	angle = 0.0f;
	animation.back()->Play();
}
void PacMan::Update(const float& dt)
{
	// Do some movement calculations
	if(dir.y == -1)
	{
		angle = 4.71239f;
		animation.back()->SetFlip(true, false, true);
	}
	if(dir.x == -1)
	{
		angle = 0.0f;
		animation.back()->SetFlip(false, false, true);
		
	}
	if(dir.y == 1)
	{
		angle = 4.71239f;
		animation.back()->SetFlip(false, false, true);
	}
	if(dir.x == 1)
	{
		angle = 0.0f;
		animation.back()->SetFlip(true, false, true);	
	}
	pos.x+=dir.x * speed * dt;
	pos.y+=dir.y * speed * dt;
	animation.back()->Update(dt);
}
void PacMan::Render()
{
	//sprite->Render(pos.x, pos.y);
}
void PacMan::Render(const float& sizeX, const float& sizeY)
{
	animation.back()->RenderEx(pos.x, pos.y, angle, sizeX * 2.0f, sizeY * 2.0f);
	//sprite->RenderEx(pos.x, pos.y, 0.0f, sizeX * 2.0f, sizeY * 2.0f);
}
void PacMan::LoadResources()
{
	tex=hge->Texture_Load("pacman.png");
	if(!tex)
	{
		throw(std::exception("Can't find pacman.png"));
	}
	animation.push_back(new hgeAnimation(tex, 3, 6, 2, 2, 16, 16)); 
	//sprite = new hgeSprite(tex, 2, 2, 14, 14);
	//sprite=new hgeSprite(tex, 96, 64, 32, 32);
	//animation->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	animation.back()->SetHotSpot(7,7);
}
void PacMan::FreeResources()
{
	hge->Texture_Free(tex);
	
}
PacMan::~PacMan()
{
	FreeResources();
	while(!animation.empty())
	{
		delete animation.back();
		animation.pop_back();
	}
	
}