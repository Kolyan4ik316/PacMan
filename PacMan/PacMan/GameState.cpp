#include "GameState.h"
//PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	// Setting place for our tiles
	const float offset = 36.0f;
	float prevX = originX / scaleX - 360.0f;
	float prevY = originY / scaleY - 285.0f;
	nMapWidth = 20;
	nMapHeight = 16;
	for(unsigned int i = 0; i < nMapHeight; i++)
	{
		for (unsigned int j = 0; j < nMapWidth; j++)
		{
			tiles.push_back(new Tiles(hge, hgeVector(prevX , prevY), scaleX, scaleY));
			prevX += offset;
			
		}
		prevX = originX / scaleX - 360.0f;
		prevY += offset;
	}
	for (unsigned int x = 0; x < nMapWidth; x++)
	{
			for (unsigned int y = 0; y < nMapHeight; y++)
			{
				if (y > 0)
					tiles[y * nMapWidth + x]->vecNeighbours.push_back(tiles[(y - 1) * nMapWidth + (x + 0)]);
				if (y < nMapHeight - 1)
					tiles[y * nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 1) * nMapWidth + (x + 0)]);
				if (x > 0)
					tiles[y * nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 0) * nMapWidth + (x - 1)]);
				if (x < nMapWidth - 1)
					tiles[y * nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 0) * nMapWidth + (x + 1)]);
				
				//remove this because ghost trying to go diagnoly thru obstacles
				/*if (y>0 && x>0)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y - 1) * nMapWidth + (x - 1)]);
				if (y<nMapHeight-1 && x>0)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 1) * nMapWidth + (x - 1)]);
				if (y>0 && x<nMapWidth-1)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y - 1) * nMapWidth + (x + 1)]);
				if (y<nMapHeight - 1 && x<nMapWidth-1)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 1) * nMapWidth + (x + 1)]);
				*/	
			}
	}

	LoadResources();
	quit = false;
	for (unsigned int x = 0; x < nMapWidth; x++)
	{
		for (unsigned int y = 0; y < nMapHeight; y++)
		{
			tiles[y * nMapWidth + x]->parent = NULL;
			tiles[y * nMapWidth + x]->fGlobalGoal = std::numeric_limits<float>::infinity();
			tiles[y * nMapWidth + x]->fLocalGoal = std::numeric_limits<float>::infinity();
			tiles[y * nMapWidth + x]->bVisited = false;
		}
	}
	// Setting position of player;
	player->SetPosition(hgeVector(tiles.at(nMapHeight /2 * nMapWidth + nMapWidth/2)->GetOrigin()));
	player->SetSize(scaleX, scaleY);
	ghost->SetPosition(hgeVector(tiles.at(nMapHeight * nMapWidth / 2)->GetOrigin()));
	//ghost->nodeStart = tiles.at(nMapHeight / 2 * nMapWidth / 2 + 1);
	obst->SetPosition(hgeVector(tiles.at(nMapHeight / 2 * nMapWidth / 2 - 11)->GetPosition()));
	tiles.at(nMapHeight / 2 * nMapWidth / 2 - 11)->HaveObstacles(true);
	food->SetPosition(tiles.at(nMapHeight / 2 * nMapWidth / 2 + 11)->GetOrigin());
}
void GameState::LoadResources()
{
	player = new PacMan(hge);
	ghost = new Ghost(hge);
	obst = new Obstacles(hge);
	food = new Food(hge);
	pathfinder = new PathFinder(nMapWidth, nMapHeight, &tiles);
}

void GameState::UpdateEnemies()
{
	hgeVector dir = hgeVector(0.0f, 0.0f);
	
	pathfinder->SolveA_Star(ghost);
	
	
	std::list<Tiles*> chooseList;
	for(unsigned int i = 0; i < ghost->nodeStart->vecNeighbours.size(); i++)
	{
		if(ghost->nodeStart->vecNeighbours.at(i)->parent == ghost->nodeStart)
		{
			if(ghost->nodeStart->vecNeighbours.at(i)->ObstaclesInside() == false)
			{
				chooseList.push_back(ghost->nodeStart->vecNeighbours.at(i));
			}
			
		}
	}
	if(!chooseList.empty())
	{
		chooseList.sort(pathfinder->LessfGlobalGoal);
		if(ghost->IsColiding(obst->Rectangle()))
		{
			if(ghost->Rectangle()->x1 < obst->Rectangle()->x1)
			{
				
				if(ghost->GetPosition().y < chooseList.front()->GetOrigin().y)
				{
					dir = hgeVector(0.0f, 1.0f);
				}
				else
				{
					dir = hgeVector(0.0f, -1.0f);
				}
				dir -= hgeVector(1.0f, 0.0f);
			}
			if(ghost->Rectangle()->x2 > obst->Rectangle()->x2)
			{
				
				if(ghost->GetPosition().y < chooseList.front()->GetOrigin().y)
				{
					dir = hgeVector(0.0f, 1.0f);
				}
				else
				{
					dir = hgeVector(0.0f, -1.0f);
				}
				dir += hgeVector(1.0f, 0.0f);
			}
			if(ghost->Rectangle()->y1 < obst->Rectangle()->y1)
			{
				
				if(ghost->GetPosition().x < chooseList.front()->GetOrigin().x)
				{
					dir = hgeVector(1.0f, 0.0f);
				}
				else
				{
					dir = hgeVector(-1.0f, 0.0f);
				}
				dir -= hgeVector(0.0f, 1.0f);
			}
			if(ghost->Rectangle()->y2 > obst->Rectangle()->y2)
			{
				
				if(ghost->GetPosition().x < chooseList.front()->GetOrigin().x)
				{
					dir = hgeVector(1.0f, 0.0f);
				}
				else
				{
					dir = hgeVector(-1.0f, 0.0f);
				}
				dir += hgeVector(0.0f, 1.0f);
			}
		}
		else
		{
			{
				ghost->SetDestination(chooseList.front()->GetOrigin());
				if(ghost->GetPosition().x > chooseList.front()->GetOrigin().x)
				{
					dir -= hgeVector(1.0f, 0.0f);
				}
				if(ghost->GetPosition().x < chooseList.front()->GetOrigin().x)
				{
					dir += hgeVector(1.0f, 0.0f);
				}
				if(ghost->GetPosition().y < chooseList.front()->GetOrigin().y)
				{
					dir += hgeVector(0.0f, 1.0f);
				}
				if(ghost->GetPosition().y > chooseList.front()->GetOrigin().y)
				{
					dir -= hgeVector(0.0f, 1.0f);
				}
			}
		}
	}
	else
	{
		if(ghost->GetPosition().x > ghost->nodeEnd->GetOrigin().x)
		{
			dir -= hgeVector(1.0f, 0.0f);
		}
		if(ghost->GetPosition().x < ghost->nodeEnd->GetOrigin().x)
		{
			dir += hgeVector(1.0f, 0.0f);
		}
		if(ghost->GetPosition().y < ghost->nodeEnd->GetOrigin().y)
		{
			dir += hgeVector(0.0f, 1.0f);
		}
		if(ghost->GetPosition().y > ghost->nodeEnd->GetOrigin().y)
		{
			dir -= hgeVector(0.0f, 1.0f);
		}
	}
	
	
	
	ghost->SetDirection(dir);
}
void GameState::Update(const float& dt)
{	

	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		if(tiles.at(i)->IsInside(player->GetPosition()))
		{
			ghost->nodeEnd = tiles.at(i);
		}
		
		if(tiles.at(i)->IsInside(ghost->GetPosition()))
		{
			ghost->nodeStart = tiles.at(i);
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
	if(player->IsColiding(food->Rectangle()))
	{
		food->EatFood();
	}
	//ghost->MoveTo(player->GetPosition(), dt);
	ghost->Update(dt);
	obst->Update(dt);
	if(!food->IsEaten())
	{
		food->Update(dt);
	}
	
	
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
	if(!food->IsEaten())
	{
		food->Render();
	}
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
	delete food;
	delete pathfinder;
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