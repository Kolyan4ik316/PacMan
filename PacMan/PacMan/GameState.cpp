#include "GameState.h"
bool GameState::isLoadedResources = false;
PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	// Setting position of player;
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
	// Updating player state
	player.Update(hge, dt);
	
}
void GameState::Render()
{
	// I'm gonna to chane this later;
	if(!isLoadedResources)
	{
		LoadResources();
		isLoadedResources = true;
	}
	// rendering player
	player.Render(hge);
}
void GameState::UpdateInput(const float& dt)
{	
	// This way of implementation it takes much better
	// and smoother control of player position
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
	// Input to back to main menu
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