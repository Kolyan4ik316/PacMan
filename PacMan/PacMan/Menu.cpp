#include "Menu.h"
Menu::Menu(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	quit = false;
	LoadResources();
	gui=new hgeGUI();
}
void Menu::LoadResources()
{
	bgText = hge->Texture_Load("PacManBackGround.png");
	if(!bgText)
	{
		throw(std::exception("Can't find cursor.png or PacManBackGround.png"));
	}
	tex=hge->Texture_Load("cursor.png");
	snd=hge->Effect_Load("menu.wav");
	if(!tex || !snd)
	{
		throw(std::exception("Can't find cursor.png or menu.wav"));
	}
	fnt = NULL;
	fnt=new hgeFont("font1.fnt");
	if(!fnt)
	{
		throw(std::exception("Can't find font1.fnt"));
	}
	spr=new hgeSprite(tex,0,0,32,32);
	bgSpr =new hgeSprite(bgText,0,0,1280,720);
	
}
void Menu::UpdateBG(const float& dt)
{
}
void Menu::FreeResources()
{
	delete gui;
	delete fnt;
	delete spr;
	delete bgSpr;
	
	hge->Effect_Free(snd);
	hge->Texture_Free(tex);
	hge->Texture_Free(bgText);
}
Menu::~Menu()
{
	FreeResources();
}