#include "GameState.h"
//PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	// Setting place for our tiles
	const float offset = 36.0f;
	float prevX = originX / scaleX - 360.0f;
	float prevY = originY / scaleY - 285.0f;
	
	for(unsigned int i = 0; i < 16; i++)
	{
		for (unsigned int j = 0; j < 20; j++)
		{
			tiles.push_back(new Tiles(hge, hgeVector(prevX , prevY), scaleX, scaleY));
			prevX += offset;
			
		}
		prevX = originX / scaleX - 360.0f;
		tiles.push_back(new Tiles(hge, hgeVector(prevX, prevY), scaleX, scaleY));
		prevY += offset;
	}
	LoadResources();
	quit = false;
	// Setting position of player;
	player->SetPosition(hgeVector(tiles.at(20 * 9 - 2)->GetOrigin()));
	player->SetSize(scaleX, scaleY);
	ghost->SetPosition(hgeVector(tiles.at(20 * 3 + 6)->GetOrigin()));
	obst->SetPosition(hgeVector(tiles.at(4 * 12 + 16)->GetPosition()));
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
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if(tiles.at(i)->GoalInside())
		{
			ghost->SetDestination(tiles.at(i)->GetOrigin());
			if(ghost->GetPosition().x > tiles.at(i)->GetOrigin().x)
			{
				dir -= hgeVector(1.0f, 0.0f);
			}
			if(ghost->GetPosition().x < tiles.at(i)->GetOrigin().x)
			{
				dir += hgeVector(1.0f, 0.0f);
			}
			if(ghost->GetPosition().y < tiles.at(i)->GetOrigin().y)
			{
				dir += hgeVector(0.0f, 1.0f);
			}
			if(ghost->GetPosition().y > tiles.at(i)->GetOrigin().y)
			{
				dir -= hgeVector(0.0f, 1.0f);
			}
			break;
		}
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
		if(tiles.at(i)->IsInside(player->GetPosition()))
		{
			tiles.at(i)->HaveGoal(true);
		}
		else
		{
			tiles.at(i)->HaveGoal(false);
		}
		
	}
	// Process keys
	UpdateInput(dt);
	// Updating player state
	player->Update(dt);
	UpdateEnemies();
	if(player->IsColiding(ghost->Rectangle()))
	{
		ghost->SetPosition(hgeVector(tiles.at(20 * 9 - 2)->GetOrigin()));
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
	player->Render();
	ghost->Render();
	ghost->RenderLineToGoal();
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
		player->SetPosition(hgeVector(tiles.at(20 * 9 - 2)->GetOrigin()));
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