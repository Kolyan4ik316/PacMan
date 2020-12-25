#include "GameState.h"
hgeQuad GameState::quad = {};
HEFFECT GameState::snd = 0;
float GameState::dx = 0.0f;
float GameState::dy = 0.0f;
float GameState::x = 100.0f;
float GameState::y = 100.0f;
const float GameState::speed = 90;
const float GameState::friction = 0.98f;
bool GameState::isLoadedResources = false;
PacMan GameState::player = PacMan();
GameState::GameState()
{
}
void GameState::LoadResources(HGE *hge)
{
	if(!hge)
	{
		throw(std::exception("HGE is nullptr"));
	}
	// Load sound and texture
	snd=hge->Effect_Load("menu.wav");
	quad.tex=hge->Texture_Load("particles.png");
	player.LoadResources(hge);
	if(!snd || !quad.tex)
	{
		throw(std::exception("Can't find sound or texture"));
	}
	
	quad.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;

	for(int i=0;i<4;i++)
	{
		// Set up z-coordinate of vertices
		quad.v[i].z=0.5f;
		// Set up color. The format of DWORD col is 0xAARRGGBB
		quad.v[i].col=0xFFFFA000;
	}

	// Set up quad's texture coordinates.
	// 0,0 means top left corner and 1,1 -
	// bottom right corner of the texture.
	quad.v[0].tx=96.0/128.0; quad.v[0].ty=64.0/128.0; 
	quad.v[1].tx=128.0/128.0; quad.v[1].ty=64.0/128.0; 
	quad.v[2].tx=128.0/128.0; quad.v[2].ty=96.0/128.0; 
	quad.v[3].tx=96.0/128.0; quad.v[3].ty=96.0/128.0;
}
bool GameState::Update(HGE *hge, const float dt)
{
	// Get the time elapsed since last call of FrameFunc().
	// This will help us to synchronize on different
	// machines and video modes.
	player.LoadResources(hge);
	// Process keys
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_LEFT)) dx-=speed*dt;
	if (hge->Input_GetKeyState(HGEK_RIGHT)) dx+=speed*dt;
	if (hge->Input_GetKeyState(HGEK_UP)) dy-=speed*dt;
	if (hge->Input_GetKeyState(HGEK_DOWN)) dy+=speed*dt;

	// Do some movement calculations and collision detection	
	dx*=friction; dy*=friction; x+=dx; y+=dy;
	if(x>784) {x=784-(x-784);dx=-dx;boom(hge);}
	if(x<16) {x=16+16-x;dx=-dx;boom(hge);}
	if(y>584) {y=584-(y-584);dy=-dy;boom(hge);}
	if(y<16) {y=16+16-y;dy=-dy;boom(hge);}

	// Set up quad's screen coordinates
	quad.v[0].x=x-16; quad.v[0].y=y-16;
	quad.v[1].x=x+16; quad.v[1].y=y-16;
	quad.v[2].x=x+16; quad.v[2].y=y+16;
	quad.v[3].x=x-16; quad.v[3].y=y+16;

	// Continue execution
	return false;
}
void GameState::Render(HGE *hge)
{
	if(!hge)
	{
		throw(std::exception("HGE is nullptr"));
	}
	if(!isLoadedResources)
	{
		LoadResources(hge);
		isLoadedResources = true;
	}
	//Begin rendering quads.
	// This function must be called
	// before any actual rendering.
	hge->Gfx_BeginScene();

	// Clear screen with black color
	hge->Gfx_Clear(0);
	
	// Render quads here. This time just
	// one of them will serve our needs.
	hge->Gfx_RenderQuad(&quad);
	player.Render(hge);

	// End rendering and update the screen
	hge->Gfx_EndScene();
}
void GameState::UpdateInput(const float dt)
{
	
}
void GameState::FreeResources(HGE* hge)
{
	hge->Texture_Free(quad.tex);
	hge->Effect_Free(snd);
	player.FreeResources(hge);
}
GameState::~GameState()
{
	
}