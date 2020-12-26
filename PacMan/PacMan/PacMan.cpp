#include "PacMan.h"
hgeSprite* PacMan::sprite = 0;
HTEXTURE PacMan::tex = 0;
float Entity::pos_x = 0;
float Entity::pos_y = 0;
float Entity::dir_x = 0;
float Entity::dir_y = 0;
HEFFECT PacMan::snd = 0;
const float PacMan::speed = 90;
//const float PacMan::friction = 0.98f;
PacMan::PacMan()
{
	pos_x = 300.0f;
	pos_y = 400.0f;
}
void PacMan::Update(HGE *hge, const float dt)
{
	// Do some movement calculations and collision detection	
	pos_x+=dir_x * speed * dt; 
	pos_y+=dir_y * speed * dt;
	//if(x>784) {x=784-(x-784);dx=-dx;boom(hge);}
	//if(x<16) {x=16+16-x;pos_x=-pos_x;boom(hge);}
	//if(y>584) {y=584-(y-584);pos_y=-pos_y;boom(hge);}
	//if(y<16) {y=16+16-y;pos_y=-pos_y;boom(hge);}
}
void PacMan::Render(HGE* hge)
{
	sprite->Render(pos_x, pos_y);
}
void PacMan::LoadResources(HGE *hge)
{
	tex=hge->Texture_Load("particles.png");
	snd=hge->Effect_Load("menu.wav");
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