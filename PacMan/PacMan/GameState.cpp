#include "GameState.h"
bool GameState::isLoadedResources = false;
//PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	// We are gonna latter add option class and we will can switch for resolution 4:3 16:9 16:10 etc
	LoadResources();
	quit = false;
	// Setting position of player;
	player->SetPosition(hgeVector(originX, originY));
	ghost->SetPosition(hgeVector(originX + 100.0f, originY + 100.0f));
}
void GameState::LoadResources()
{
	player = new PacMan(hge);
	ghost = new Ghost(hge);
	//player->LoadResources();
}
void GameState::UpdateEnemies()
{
	hgeVector dir = hgeVector(0.0f, 0.0f);
	ghost->SetDestination(player->GetPosition());
	if(ghost->GetPosition().x > player->GetPosition().x)
	{
		dir -= hgeVector(1.0f, 0.0f);
	}
	if(ghost->GetPosition().x < player->GetPosition().x)
	{
		dir += hgeVector(1.0f, 0.0f);
	}
	if(ghost->GetPosition().y < player->GetPosition().y)
	{
		dir += hgeVector(0.0f, 1.0f);
	}
	if(ghost->GetPosition().y > player->GetPosition().y)
	{
		dir -= hgeVector(0.0f, 1.0f);
	}
	ghost->SetDirection(dir);
}
void GameState::Update(const float& dt)
{	
	// Process keys
	UpdateInput(dt);
	// Updating player state
	player->Update(dt);
	UpdateEnemies();
	if(player->IsColiding(ghost->Rectangle()))
	{
		ghost->SetPosition(hgeVector(originX, originY));
	}
	//ghost->MoveTo(player->GetPosition(), dt);
	ghost->Update(dt);
	
}
void GameState::Render()
{
	// rendering player
	player->Render(scaleX, scaleY);
	ghost->Render(scaleX, scaleY);
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
		player->SetPosition(hgeVector(originX, originY));
	};
	// Input to back to main menu
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		EndState();
	};
	player->SetDirection(dir);

}
void GameState::FreeResources()
{
	//player->FreeResources();
	delete ghost;
	delete player;
}
GameState::~GameState()
{
	FreeResources();
}