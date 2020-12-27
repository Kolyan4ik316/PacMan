#include "PacMan.h"
hgeSprite* PacMan::sprite = 0;
HTEXTURE PacMan::tex = 0;
HEFFECT PacMan::snd = 0;
const float PacMan::speed = 90;
//const float PacMan::friction = 0.98f;
PacMan::PacMan()
{
}
void PacMan::Update(HGE *hge, const float& dt)
{
	// Do some movement calculations
	pos.x+=dir.x * speed * dt; 
	pos.y+=dir.y * speed * dt;
}
void PacMan::Render(HGE* hge)
{
	sprite->Render(pos.x, pos.y);
}
void PacMan::LoadResources(HGE *hge)
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
void PacMan::FreeResources(HGE* hge)
{
	hge->Texture_Free(tex);
	
}
PacMan::~PacMan()
{
	delete sprite;
	sprite = 0;
	
}