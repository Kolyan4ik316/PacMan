#include "GameState.h"
//PacMan GameState::player = PacMan();
GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	// Setting place for our tiles
	eatenFood = 0;
	const float offset = 36.0f;
	float prevX = originX / scaleX - 400.0f;
	float prevY = originY / scaleY - 300.0f;
	nMapWidth = 20;
	nMapHeight = 16;
	for(unsigned int i = 0; i < nMapHeight; i++)
	{
		for (unsigned int j = 0; j < nMapWidth; j++)
		{
			tiles.push_back(new Tiles(hge, hgeVector(prevX , prevY), scaleX, scaleY));
			prevX += offset;
			
		}
		prevX = originX / scaleX - 400.0f;
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
	for(unsigned int i = 0; i <mapItems.size(); i++)
	{
		if(typeid(Obstacles) == typeid(*mapItems.at(i)))
		{
			obsts.push_back((Obstacles*)mapItems.at(i));
		}
		if(typeid(Food) == typeid(*mapItems.at(i)))
		{
			foods.push_back((Food*)mapItems.at(i));
		}
	}
	player->SetPosition(hgeVector(tiles.at(nMapHeight /2 * nMapWidth + nMapWidth/2)->GetOrigin()));
	player->SetSize(scaleX, scaleY);
}
void GameState::LoadResources()
{
	player = new PacMan(hge);
	mapManager = new MapManager(hge, &mapItems, &tiles, nMapWidth, nMapHeight);
	mapManager->LoadMap();
	pathfinder = new PathFinder(nMapWidth, nMapHeight, &tiles);
}
const bool GameState::CheckForColiding(DynamicEntity* checker, Entity* colisior) const
{
	return checker->IsColiding(colisior->Rectangle());
}
void GameState::Colision(DynamicEntity* checker, Entity* colisior)
{
	hgeVector dir = hgeVector(0.0f, 0.0f);
	if(checker->Rectangle()->x1 < colisior->Rectangle()->x1)
	{
		dir -= hgeVector(8.0f, 0.0f);
	}
	if(checker->Rectangle()->x2 > colisior->Rectangle()->x2)
	{
		dir += hgeVector(8.0f, 0.0f);
	}
	if(checker->Rectangle()->y1 < colisior->Rectangle()->y1)
	{
		dir -= hgeVector(0.0f, 8.0f);
	}
	if(checker->Rectangle()->y2 > colisior->Rectangle()->y2)
	{
		dir += hgeVector(0.0f, 8.0f);
	}
	checker->SetDirection(dir);
	
}
void GameState::UpdateEnemies(Ghost* ghost)
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
	/*for(unsigned int i = 0; i < mapItems.size(); i++)
	{
		mapItems.at(i)->Update(dt);
	}*/
	UpdateInput(dt);
	
	for(unsigned int i = 0; i < obsts.size(); i++)
	{
		if(CheckForColiding(player, obsts.at(i)))
		{
			Colision(player, obsts.at(i));
			break;
		}
		obsts.at(i)->Update(dt);
	}
	for(unsigned int i = 0; i < foods.size(); i++)
	{
		if(!foods.at(i)->IsEaten())
		{
			foods.at(i)->Update(dt);
			if(CheckForColiding(player, foods.at(i)))
			{
				foods.at(i)->EatFood();
				eatenFood++;
			}
		}
	}
	if(eatenFood == foods.size())
	{
		EndState();
	}
	player->Update(dt);
	tiles.at(0)->
	// Process keys
	// Updating player state
	
	/*if(player->IsColiding(ghost->Rectangle()))
	{
		ghost->SetPosition(hgeVector(tiles.at(20 * 9 - 2)->GetOrigin()));
	}
	if(player->IsColiding(food->Rectangle()))
	{
		food->EatFood();
	}
	if(player->IsColiding(holyFood->Rectangle()))
	{
		holyFood->EatFood();
	}
	//ghost->MoveTo(player->GetPosition(), dt);
	ghost->Update(dt);
	obst->Update(dt);
	if(!food->IsEaten())
	{
		food->Update(dt);
	}
	if(!holyFood->IsEaten())
	{
		holyFood->Update(dt);
	}*/
	
}
void GameState::Render()
{
	/*for(unsigned int i = 0; i < mapItems.size(); i++)
	{
		mapItems.at(i)->Render();
	}*/
	for(unsigned int i = 0; i <obsts.size(); i++)
	{
		obsts.at(i)->Render();
	}
	for(unsigned int i = 0; i <foods.size(); i++)
	{
		if(!foods.at(i)->IsEaten())
		{
			foods.at(i)->Render();
		}
	}
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles.at(i)->Render();
	}
	// rendering player
	player->Render();
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
		states->push(new GamePause(states, hge));
	};
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		EndState();
	};

	/*if(player->IsColiding(obst->Rectangle()))
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
	}*/

	player->SetDirection(dir);

}
void GameState::FreeResources()
{
	delete player;
	
	delete pathfinder;
	delete mapManager;
	for (unsigned int i = 0; i < foods.size(); i++)
	{
		foods.at(i)->FreeResources();
	}
	while(!mapItems.empty())
	{
		delete mapItems.back();
		mapItems.pop_back();
	}
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