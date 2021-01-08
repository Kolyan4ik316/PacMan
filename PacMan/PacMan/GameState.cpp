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
		tiles.push_back(new Tiles(hge, hgeVector(prevX, prevY), scaleX, scaleY));
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
				
				if (y>0 && x>0)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y - 1) * nMapWidth + (x - 1)]);
				if (y<nMapHeight-1 && x>0)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 1) * nMapWidth + (x - 1)]);
				if (y>0 && x<nMapWidth-1)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y - 1) * nMapWidth + (x + 1)]);
				if (y<nMapHeight - 1 && x<nMapWidth-1)
					tiles[y*nMapWidth + x]->vecNeighbours.push_back(tiles[(y + 1) * nMapWidth + (x + 1)]);
					
			}
	}

	LoadResources();
	quit = false;
	for (unsigned int x = 0; x < nMapWidth; x++)
	{
		for (unsigned int y = 0; y < nMapHeight; y++)
		{
			tiles[y * nMapWidth + x]->parent = NULL;
			tiles[y * nMapWidth + x]->bVisited = false;
		}
	}
	// Setting position of player;
	player->SetPosition(hgeVector(tiles.at(20 * 9 - 2)->GetOrigin()));
	player->SetSize(scaleX, scaleY);
	ghost->SetPosition(hgeVector(tiles.at(20 * 3 + 6)->GetOrigin()));
	ghost->nodeStart = tiles.at(20 * 3 + 6);
	obst->SetPosition(hgeVector(tiles.at(10 * 9 - 2)->GetPosition()));
}
void GameState::LoadResources()
{
	player = new PacMan(hge);
	ghost = new Ghost(hge);
	obst = new Obstacles(hge);
	//player->LoadResources();
}
float GameState::Distance(Tiles* a, Tiles* b)
{
	return sqrtf((a->pos.x - b->pos.x) * (a->pos.x - b->pos.x) + (a->pos.y - b->pos.y) * (a->pos.y - b->pos.y));
}
float GameState::Heuristic(Tiles* a, Tiles* b)
{
	return Distance(a, b);
}
void GameState::SolveA_Star()
{
	// Reset Navigation Graph - default all node states
	for (unsigned int x = 0; x < nMapWidth; x++)
	{
		for (unsigned int y = 0; y < nMapHeight; y++)
		{
			tiles[y * nMapWidth + x]->bVisited = false;
			tiles[y * nMapWidth + x]->fGlobalGoal = std::numeric_limits<float>::infinity();
			tiles[y * nMapWidth + x]->fLocalGoal = std::numeric_limits<float>::infinity();
			tiles[y * nMapWidth + x]->parent = NULL;	// No parents
		}
	}
	Tiles* nodeCurrent = ghost->nodeStart;
	ghost->nodeStart->fLocalGoal = 0.0f;
	ghost->nodeStart->fGlobalGoal = Heuristic(ghost->nodeStart, ghost->nodeEnd);

	std::list<Tiles*> listNotTestedNodes;
	listNotTestedNodes.push_back(ghost->nodeStart);
	while (!listNotTestedNodes.empty() && nodeCurrent != ghost->nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
	{
		listNotTestedNodes.sort(LessfGlobalGoal);
	
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
		{
			listNotTestedNodes.pop_front();
		}
		if (listNotTestedNodes.empty())
		{
			break;
		}
		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true; // We only explore a node once	
		for (unsigned int i = 0; i <nodeCurrent->vecNeighbours.size(); i++)
		{
			if (!nodeCurrent->vecNeighbours.at(i)->bVisited && nodeCurrent->vecNeighbours.at(i)->ObstaclesInside() == false)
			{
				listNotTestedNodes.push_back(nodeCurrent->vecNeighbours.at(i));
			}
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + Distance(nodeCurrent, nodeCurrent->vecNeighbours.at(i));
			if (fPossiblyLowerGoal < nodeCurrent->vecNeighbours.at(i)->fLocalGoal)
			{
				nodeCurrent->vecNeighbours.at(i)->parent = nodeCurrent;
				nodeCurrent->vecNeighbours.at(i)->fLocalGoal = fPossiblyLowerGoal;

				nodeCurrent->vecNeighbours.at(i)->fGlobalGoal = nodeCurrent->vecNeighbours.at(i)->fLocalGoal + Heuristic(nodeCurrent->vecNeighbours.at(i), ghost->nodeEnd);
			}
		}
	}	

}
void GameState::UpdateEnemies()
{
	hgeVector dir = hgeVector(0.0f, 0.0f);
	SolveA_Star();
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
	chooseList.sort(LessfGlobalGoal);
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
			ghost->nodeEnd = tiles.at(i);
		}
		else
		{
			tiles.at(i)->HaveGoal(false);
		}
		if(tiles.at(i)->IsInside(ghost->GetPosition()))
		{
			ghost->nodeStart = tiles.at(i);
		}
		if(tiles.at(i)->IsInside(obst->GetPosition()))
		{
			tiles.at(i)->HaveObstacles(true);
		}
		else
		{
			tiles.at(i)->HaveObstacles(false);
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