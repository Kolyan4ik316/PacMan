#include "GameState.h"
bool GameState::isLoadedResources = false;
//PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	// We are gonna latter add option class and we will can switch for resolution 4:3 16:9 16:10 etc
	const float offset = 30.0f;
	float prevX = 0.0f;
	float prevY = 0.0f;
	for(unsigned int i = 0; i < 26; i++)
	{
		tiles.push_back(new Tiles(hge));
		tiles.back()->SetPosition(hgeVector(prevX, prevY));
		prevX += offset;
	}
	
	LoadResources();
	quit = false;
	// Setting position of player;
	player->SetPosition(hgeVector(originX, originY));
	ghost->SetPosition(hgeVector(originX + 100.0f, originY + 100.0f));
	obst->SetPosition(hgeVector(originX + 200.0f, originY + 200.0f));
}
void GameState::LoadResources()
{
	player = new PacMan(hge);
	ghost = new Ghost(hge);
	obst = new Obstacles(hge);
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
	if(ghost->IsColiding(obst->Rectangle()))
	{
		if(ghost->Rectangle()->x1 < obst->Rectangle()->x1)
		{
			dir -= hgeVector(1.0f, 0.0f);
		}
		if(ghost->Rectangle()->x2 > obst->Rectangle()->x2)
		{
			dir += hgeVector(1.0f, 0.0f);
		}
		if(ghost->Rectangle()->y1 < obst->Rectangle()->y1)
		{
			dir -= hgeVector(0.0f, 1.0f);
		}
		if(ghost->Rectangle()->y2 > obst->Rectangle()->y2)
		{
			dir += hgeVector(0.0f, 1.0f);
		}
	}
	ghost->SetDirection(dir);
}
void GameState::Update(const float& dt)
{	
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles.at(i)->Update(dt);
	}
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
	obst->Update(dt);
	
}
void GameState::Render()
{
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles.at(i)->Render();
	}
	// rendering player
	player->Render(scaleX, scaleY);
	ghost->Render(scaleX, scaleY);
	obst->Render();
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

	if(player->IsColiding(obst->Rectangle()))
	{
		if(player->Rectangle()->x1 < obst->Rectangle()->x1)
		{
			dir -= hgeVector(1.0f, 0.0f);
		}
		if(player->Rectangle()->x2 > obst->Rectangle()->x2)
		{
			dir += hgeVector(1.0f, 0.0f);
		}
		if(player->Rectangle()->y1 < obst->Rectangle()->y1)
		{
			dir -= hgeVector(0.0f, 1.0f);
		}
		if(player->Rectangle()->y2 > obst->Rectangle()->y2)
		{
			dir += hgeVector(0.0f, 1.0f);
		}
	}

	player->SetDirection(dir);

}
void GameState::FreeResources()
{
	//player->FreeResources();
	delete ghost;
	delete player;
	delete obst;
}
GameState::~GameState()
{
	FreeResources();
	while(!tiles.empty())
	{
		delete tiles.back();
		tiles.pop_back();
	}
}