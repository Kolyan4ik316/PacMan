#include "Menu.h"
Menu::Menu(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	quit = false;
	LoadResources();
	gui=new hgeGUI();
	
	
	// Set up the quad we will use for background animation
	quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

	for(int i=0;i<4;i++)
	{
		// Set up z-coordinate of vertices
		quad.v[i].z=0.5f;
		// Set up color. The format of DWORD col is 0xAARRGGBB
		quad.v[i].col=0xFFFFFFFF;
	}

	quad.v[0].x=0; quad.v[0].y=0; 
	quad.v[1].x=(float)screenWidth; quad.v[1].y=0; 
	quad.v[2].x=(float)screenWidth; quad.v[2].y = (float)screenHeight; 
	quad.v[3].x=0; quad.v[3].y=(float)screenHeight; 
	
}
void Menu::LoadResources()
{
	quad.tex=hge->Texture_Load("bg.png");
	if(!quad.tex)
	{
		throw(std::exception("Can't find bg.png"));
	}
	tex=hge->Texture_Load("cursor.png");
	snd=hge->Effect_Load("menu.wav");
	if(!tex || !snd)
	{
		throw(std::exception("Can't find cursor.png or menu.wav"));
	}
	fnt = 0;
	fnt=new hgeFont("font1.fnt");
	if(!fnt)
	{
		throw(std::exception("Can't find font1.fnt"));
	}
	spr=new hgeSprite(tex,0,0,32,32);
}
void Menu::UpdateBG(const float& dt)
{
	static float t=0.0f;
	float tx,ty;

	// Here we update our background animation
	t+=dt;
	tx=50*cosf(t/60);
	ty=50*sinf(t/60);

	quad.v[0].tx=tx;        quad.v[0].ty=ty;
	quad.v[1].tx=tx+screenWidth/64; quad.v[1].ty=ty;
	quad.v[2].tx=tx+screenWidth/64; quad.v[2].ty=ty+screenHeight/64;
	quad.v[3].tx=tx;        quad.v[3].ty=ty+screenHeight/64;

}
void Menu::FreeResources()
{
	delete gui;
	delete fnt;
	delete spr;
	hge->Effect_Free(snd);
	hge->Texture_Free(tex);
}
Menu::~Menu()
{
}