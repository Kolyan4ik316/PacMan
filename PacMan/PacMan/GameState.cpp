#include "GameState.h"
bool GameState::isLoadedResources = false;
PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	quit = false;
	player.SetPosition(hgeVector(400.0f, 300.0f));
}
void GameState::LoadResources()
{
	player.LoadResources(hge);
}
void GameState::Update(const float& dt)
{	
	// Process keys
	UpdateInput(dt);
	player.Update(hge, dt);
	// Continue execution
	
}
void GameState::Render()
{
	if(!isLoadedResources)
	{
		LoadResources();
		isLoadedResources = true;
	}

	player.Render(hge);
}
void GameState::UpdateInput(const float& dt)
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
void GameState::FreeResources()
{
	player.FreeResources(hge);
}
GameState::~GameState()
{
	
}