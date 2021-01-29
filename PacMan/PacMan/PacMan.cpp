#include "PacMan.h"
PacMan::PacMan(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 170.0f;
	LoadResources();
	angle = 0.0f;
	curAnim = PacManAnimation::Common;
	prevAnim = curAnim; 
	animation.at(unsigned int(curAnim))->Play();
	wasAttacked = false;
	canBeAtacket = true;
}
void PacMan::Update(const float& dt)
{
	ChoseAnimation();
	pos.x+=dir.x * speed * scaleX * dt;
	pos.y+=dir.y * speed * scaleY * dt;
	if(!CanBeAtacket())
	{
		// Update particle system
		par->info.nEmission = 9;
		par->MoveTo(pos.x,pos.y);
		par->Update(dt);
	}
	rect.Set(pos.x - (12.0f * scaleX), pos.y - (12.0f * scaleY), pos.x + (12.0f * scaleX), pos.y + (12.0f * scaleY));
	prevAnim = curAnim; 
	animation.at(unsigned int(curAnim))->Update(dt);
	
}
const bool PacMan::WasAttacked() const
{
	return wasAttacked;
}
void PacMan::SwitchAtacked()
{
	canBeAtacket = !canBeAtacket;
}
bool PacMan::CanBeAtacket()
{
	return canBeAtacket;
}
void PacMan::SwitchWasAttacked()
{
	wasAttacked = !wasAttacked;
}
void PacMan::Render()
{
	if(curAnim == PacManAnimation::Common)
	{
		par->Render();
	}
	animation.at(unsigned int(curAnim))->RenderEx(pos.x, pos.y, angle, scaleX * 1.7f, scaleY * 1.7f);
	
	//hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y2);
}
void PacMan::LoadResources()
{
	tex=hge->Texture_Load("pacman.png");
	if(!tex)
	{
		throw(std::exception("Can't find pacman.png"));
	}
	animation.push_back(new hgeAnimation(tex, 3, 12, 2, 2, 16, 16));
	animation.back()->SetHotSpot(7,7);
	
	
	animation.push_back(new hgeAnimation(tex, 13, 12, 52, 2, 17, 15));
	animation.back()->SetHotSpot(8,8);
	//sprite = new hgeSprite(tex, 2, 2, 14, 14);
	//sprite=new hgeSprite(tex, 96, 64, 32, 32);
	
	//animation.back()->SetBlendMode(BLEND_COLORMUL |BLEND_ALPHABLEND | BLEND_NOZWRITE);
	//animation.back()->SetColor(00000000, BLEND_ALPHABLEND);
	partTex = hge->Texture_Load("particles.png");
	if(!partTex )
	{
		throw(std::exception("Can't find particles.png"));
	}
	sprite = new hgeSprite(partTex, 32, 32, 32, 32);
	sprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	//sprite->SetColor(0xFFFFA000);
	sprite->SetHotSpot(16,16);
	
	par = new hgeParticleSystem("trail.psi",sprite);
	if(!par)
	{
		throw(std::exception("Can't find trail.psi"));
	}
	
	par->Fire();
	
}
void PacMan::ChoseAnimation()
{
	// Do some movement calculations
	if(!WasAttacked())
	{
		curAnim = PacManAnimation::Common;
		if(dir.y == -1)
		{
			angle = 4.71239f;
			animation.at(unsigned int(Common))->SetFlip(true, false, true);
		}
		if(dir.x == -1)
		{
			angle = 0.0f;
			animation.at(unsigned int(Common))->SetFlip(false, false, true);
			
		}
		if(dir.y == 1)
		{
			angle = 4.71239f;
			animation.at(unsigned int(Common))->SetFlip(false, false, true);
		}
		if(dir.x == 1)
		{
			angle = 0.0f;
			animation.at(unsigned int(Common))->SetFlip(true, false, true);	
		}
	}
	else
	{
		curAnim = PacManAnimation::Attacked;
	}
	if(prevAnim != curAnim)
	{
		animation.at(unsigned int(prevAnim))->Stop();
		animation.at(unsigned int(curAnim))->Play();
	}
}
void PacMan::FreeResources()
{
	delete par;
	delete sprite;
	hge->Texture_Free(tex);
	hge->Texture_Free(partTex);
}
PacMan::~PacMan()
{
	FreeResources();	
}