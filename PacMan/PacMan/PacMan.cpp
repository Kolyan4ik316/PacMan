#include "PacMan.h"
//hgeSprite* PacMan::sprite = 0;
//HTEXTURE PacMan::tex = 0;
//HEFFECT PacMan::snd = 0;
//const float PacMan::speed = 90;
//const float PacMan::friction = 0.98f;
PacMan::PacMan(HGE* hge_in)
	:
	Entity(hge_in)
{
	tex = NULL;
	sprite = NULL;
	snd = NULL;
	speed = 90.0f;
	LoadResources();
}
void PacMan::Update(const float& dt)
{
	// Do some movement calculations
	pos.x+=dir.x * speed * dt; 
	pos.y+=dir.y * speed * dt;
}
void PacMan::Render()
{
	sprite->Render(pos.x, pos.y);
}
void PacMan::Render(const float& sizeX, const float& sizeY)
{
	sprite->RenderEx(pos.x, pos.y, 0.0f, sizeX, sizeY);
}
void PacMan::LoadResources()
{
	tex=hge->Texture_Load("particles.png");
	snd=hge->Effect_Load("menu.wav");
	if(!tex || !snd)
	{
		throw(std::exception("Can't find particles.png, or menu.wav"));
	}
	sprite=new hgeSprite(tex, 96, 64, 32, 32);
	sprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	sprite->SetHotSpot(16,16);
}
void PacMan::FreeResources()
{
	hge->Texture_Free(tex);
	
}
PacMan::~PacMan()
{
	FreeResources();
	delete sprite;
	sprite = NULL;
	
}