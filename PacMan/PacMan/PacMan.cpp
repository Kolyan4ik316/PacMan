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
	speed = 170.0f;
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
	rect.Set(pos.x - 14.0f, pos.y - 14.0f, pos.x+ 14.0f, pos.y + 14.0f);
	animation.back()->Update(dt);
}
void PacMan::Render()
{
	animation.back()->RenderEx(pos.x, pos.y, angle, scaleX * 1.7f, scaleY * 1.7f);
}
void PacMan::Render(const float& sizeX, const float& sizeY)
{
	//hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x1 + 40.0f, rect.y1);
	//hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x1, rect.y1 + 40.0f);
	//hge->Gfx_RenderLine(rect.x1  + 40.0f, rect.y1, rect.x1 + 40.0f, rect.y1 + 40.0f);
	//hge->Gfx_RenderLine(rect.x1, rect.y1  + 40.0f, rect.x1 + 40.0f, rect.y1 + 40.0f);
	
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
}