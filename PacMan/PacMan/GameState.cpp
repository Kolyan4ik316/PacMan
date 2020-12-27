#include "GameState.h"
bool GameState::isLoadedResources = false;
PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in) : State(states_in)
{
	quit = false;
	player.SetPosition(hgeVector(400.0f, 300.0f));
}
void GameState::LoadResources(HGE *hge)
{
	player.LoadResources(hge);
}
void GameState::Update(HGE *hge, const float& dt)
{	
	// Process keys
	UpdateInput(hge, dt);
	player.Update(hge, dt);
	// Continue execution
	
}
void GameState::Render(HGE *hge)
{
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
		EndState();
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