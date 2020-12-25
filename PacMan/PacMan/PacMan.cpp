#include "PacMan.h"
hgeSprite* PacMan::sprite = 0;
HTEXTURE PacMan::tex = 0;
float Entity::pos_x = 0;
float Entity::pos_y = 0;
PacMan::PacMan()
{
	pos_x = 300;
	pos_y = 400;
}
void PacMan::Update(HGE *hge, const float dt)
{
	
}
void PacMan::Render(HGE* hge)
{
	sprite->Render(pos_x, pos_y);
}
void PacMan::LoadResources(HGE *hge)
{
	tex=hge->Texture_Load("particles.png");
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
	//sprite = 0;
	delete sprite;
}