#include "Ghost.h"
Ghost::Ghost(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 90.0f;
	LoadResources();
	angle = 0.0f;
	animation->Play();
}
void Ghost::LoadResources()
{
	tex=hge->Texture_Load("pacman.png");
	if(!tex)
	{
		throw(std::exception("Can't find pacman.png"));
	}
	animation = new hgeAnimation(tex, 2, 6, 2, 17, 16, 16); 
	//sprite = new hgeSprite(tex, 2, 2, 14, 14);
	//sprite=new hgeSprite(tex, 96, 64, 32, 32);
	//animation->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	animation->SetHotSpot(7,7);
}
void Ghost::Update(const float& dt)
{
	animation->Update(dt);
}
void Ghost::Render(const float& sizeX, const float& sizeY)
{
	animation->RenderEx(pos.x, pos.y, angle, sizeX * 2.0f, sizeY * 2.0f);
}
void Ghost::FreeResources()
{
	hge->Texture_Free(tex);
}
Ghost::~Ghost()
{
	FreeResources();
	delete animation;
	sprite = NULL;
}