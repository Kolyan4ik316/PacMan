#include "GameState.h"
bool GameState::isLoadedResources = false;
PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in) : State(states_in)
{
	quit = false;
	//states = states_in;
	player.SetPosition(hgeVector(400.0f, 300.0f));
}
void GameState::LoadResources(HGE *hge)
{
	if(!hge)
	{
		throw(std::exception("HGE is nullptr"));
	}
	// Load sound and texture
	player.LoadResources(hge);

	// Set up quad's texture coordinates.
	// 0,0 means top left corner and 1,1 -
	// bottom right corner of the texture.
}
void GameState::Update(HGE *hge, const float& dt)
{
	// Get the time elapsed since last call of FrameFunc().
	// This will help us to synchronize on different
	// machines and video modes.
	//player.LoadResources(hge);
	UpdateInput(hge, dt);
	player.Update(hge, dt);
	// Process keys
	// Continue execution
}
void GameState::ToPreviousState()
{
	EndState();

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

	player.Render(hge);
}
void GameState::UpdateInput(HGE *hge, const float& dt)
{	
	hgeVector dir = hgeVector(0.0f, 0.0f);

	if(hge->Input_GetKeyState(HGEK_LEFT))
	{
		dir -= hgeVector(1.0f, 0.0f);
	};
	if(hge->Input_GetKeyState(HGEK_RIGHT))
	{
		dir += hgeVector(1.0f, 0.0f);
	};
	if(hge->Input_GetKeyState(HGEK_UP))
	{
		dir -= hgeVector(0.0f, 1.0f);
	};
	if(hge->Input_GetKeyState(HGEK_DOWN))
	{
		dir += hgeVector(0.0f, 1.0f);
	};
	if(hge->Input_GetKeyState(HGEK_SPACE))
	{
		player.SetPosition(hgeVector(400.0f, 300.0f));
	};
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		ToPreviousState();
	};
	player.SetDirection(dir);

}
void GameState::FreeResources(HGE* hge)
{
	player.FreeResources(hge);
}
GameState::~GameState()
{
	
}