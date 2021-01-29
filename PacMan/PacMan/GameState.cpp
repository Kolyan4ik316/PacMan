#include "GameState.h"

GameState::GameState(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	Tiles::SetScale(scaleX, scaleY);
	Tiles::SetOrigin(originX, originY);
	
	// Setting place for our tiles
	eatenFood = 0;
	nMapWidth = 20;
	nMapHeight = 16;
	ReleaseTimer = diffs.at(unsigned int(difficult)).release_delay;
	attackTimer = 7.0f;
	playerPunchedTimer = 0.0f;
	numOfLife = 3;
	beginTimer = 0.0f;
	sirenTimer = 0.0f;
	eatTimer = 0.0f;
	for(unsigned int i = 0; i < nMapHeight; i++)
	{
		for (unsigned int j = 0; j < nMapWidth; j++)
		{
			tiles.push_back(new Tiles(hge, hgeVector(float(j), float(i))));
		}
	}

	LoadResources();
	quit = false;
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
		if(typeid(HolyFood) == typeid(*mapItems.at(i)))
		{
			hFoods.push_back((HolyFood*)mapItems.at(i));
		}
		if(typeid(PMStartPoint) == typeid(*mapItems.at(i)))
		{
			pmstart = (PMStartPoint*)mapItems.at(i);
			player->SetPosition(mapItems.at(i)->GetWorldPosition());
			for (unsigned int i = 0; i < tiles.size(); i++)
			{
				if(tiles.at(i)->IsInside(player->GetWorldPosition()))
				{
					player->SetSpeed(diffs.at(unsigned int(difficult)).pacMan_speed);
					player->SetPosition(tiles.at(i)->GetOrigin());
					player->SetPosTile(tiles.at(i)->GetPosition());
					pmstart->SetPosTile(tiles.at(i)->GetPosition());
					pmstart->SetPosition(tiles.at(i)->GetOrigin());
				}
			}
		}
		if(typeid(GHStartPoint) == typeid(*mapItems.at(i)))
		{
			ghstart = (GHStartPoint*)mapItems.at(i);

			for (unsigned int j = 0; j < diffs.at(unsigned int(difficult)).num_of_ghosts; j++)
			{
				ghosts.push_back(new Ghost(hge));
				ghosts.back()->SetPosition(mapItems.at(i)->GetWorldPosition());
				ghosts.back()->SetSpeed(diffs.at(unsigned int(difficult)).speed_of_ghosts);
				ghosts.back()->SetPathFinder(new PathFinder(nMapWidth, nMapHeight, &tiles));
				for (unsigned int i = 0; i < tiles.size(); i++)
				{
					if(tiles.at(i)->IsInside(ghosts.back()->GetWorldPosition()))
					{
						ghosts.back()->SetPosition(tiles.at(i)->GetOrigin());
						ghosts.back()->SetPosTile(tiles.at(i)->GetPosition());
						ghstart->SetPosition(tiles.at(i)->GetOrigin());
						ghstart->SetPosTile(tiles.at(i)->GetPosition());
						break;
					}
				}
			}
			
		}
	}
	player->SetSize(scaleX, scaleY);
	hge->Effect_Play(beginSnd);
}
void GameState::LoadResources()
{
	player = new PacMan(hge);
	mapManager = new MapManager(hge, &mapItems, &tiles, nMapWidth, nMapHeight);
	mapManager->LoadMap("Maps\\SimpleMap.ini");
	beginSnd = hge->Effect_Load("Sounds\\game_start.wav");
	if(!beginSnd)
	{
		throw(std::exception("Can't find Sounds\\game_start.wav"));
	}
	sirenSnd = hge->Effect_Load("Sounds\\siren_1.wav");
	if(!sirenSnd)
	{
		throw(std::exception("Can't find Sounds\\siren_1.wav"));
	}
	wakaSnd = hge->Effect_Load("Sounds\\dp_superpac_wakka.wav");
	if(!wakaSnd)
	{
		throw(std::exception("Can't find Sounds\\dp_superpac_wakka.wav"));
	}
	deathSnd = hge->Effect_Load("Sounds\\pacman.wav");
	if(!deathSnd)
	{
		throw(std::exception("Can't find Sounds\\pacman.wav"));
	}
	eatHFoodSnd = hge->Effect_Load("Sounds\\power_pellet.wav");
	if(!eatHFoodSnd)
	{
		throw(std::exception("Can't find Sounds\\power_pellet.wav"));
	}
	eatGhostSnd = hge->Effect_Load("Sounds\\eat_ghost.wav");
	if(!eatGhostSnd)
	{
		throw(std::exception("Can't find Sounds\\eat_ghost.wav"));
	}
	fnt = NULL;
	fnt=new hgeFont("font1.fnt");
	if(!fnt)
	{
		throw(std::exception("Can't find font1.fnt"));
	}
}
const bool GameState::CheckForColiding(DynamicEntity* checker, Entity* colisior) const
{
	return checker->IsColiding(colisior->Rectangle());
}
void GameState::Colision(DynamicEntity* checker, Entity* colisior)
{
	hgeVector dir = hgeVector(0.0f, 0.0f);
	static float speed;
#ifdef _DEBUG
	speed = 1.25f;
#else
	speed = 4.25f;
#endif
	if(checker->Rectangle()->x1 < colisior->Rectangle()->x1)
	{
		dir -= hgeVector(speed, 0.0f);
	}
	if(checker->Rectangle()->x2 > colisior->Rectangle()->x2)
	{
		dir += hgeVector(speed, 0.0f);
	}
	if(checker->Rectangle()->y1 < colisior->Rectangle()->y1)
	{
		dir -= hgeVector(0.0f, speed);
	}
	if(checker->Rectangle()->y2 > colisior->Rectangle()->y2)
	{
		dir += hgeVector(0.0f, speed);
	}
	checker->SetDirection(dir);
}
void GameState::UpdateEnemies(Ghost* ghost)
{
	hgeVector dir = hgeVector(0.0f, 0.0f);
	Tiles* tempTile = NULL;
	if(!ghost->pathToTarget.empty())
	{
		tempTile = ghost->GetNextPosition();
	}
	if(tempTile)
	{
		ghost->SetDestination(tempTile->GetOrigin());
		if(ghost->GetWorldPosition().x > tempTile->GetOrigin().x)
		{
			dir -= hgeVector(1.0f, 0.0f);
		}
		if(ghost->GetWorldPosition().x < tempTile->GetOrigin().x)
		{
			dir += hgeVector(1.0f, 0.0f);
		}
		if(ghost->GetWorldPosition().y < tempTile->GetOrigin().y)
		{
			dir += hgeVector(0.0f, 1.0f);
		}
		if(ghost->GetWorldPosition().y > tempTile->GetOrigin().y)
		{
			dir -= hgeVector(0.0f, 1.0f);
		}	
	}
	
	ghost->SetDirection(dir);
}
void GameState::Update(const float& dt)
{	
	// Process keys
	if(playerPunchedTimer > 0.4f)
	{	
		UpdateInput(dt);
	}
	// Updating position of entitie by tiles
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		for(unsigned int j = 0; j < ghosts.size(); j++)
		{
			// if ghost inside tile setting his pos node pos
			if(tiles.at(i)->IsInside(ghosts.at(j)->GetWorldPosition()))
			{
				ghosts.at(j)->SetPosTile(tiles.at(i)->GetPosition());
			}
			for(unsigned int j = 0; j < ghosts.size(); j++)
			{
				if(!player->WasAttacked())
				{
					if(ghosts.at(j)->CanBeAtacket() || ghosts.at(j)->WasAttacked())
					{
						if(tiles.at(i)->IsInside(ghstart->GetWorldPosition()))
						{
							ghosts.at(j)->SetPathTo(tiles.at(i)->GetPosition());
							if(ghosts.at(j)->WasAttacked())
							{
								if(ghosts.at(j)->GetPosTile() ==  tiles.at(i)->GetPosition() && ghosts.at(j)->WasAttacked())
								{
									ghosts.at(j)->SwitchWasAtacked();
								}
								
							}
							if(ghosts.at(j)->CanBeAtacket())
							{
								if(ghosts.at(j)->GetPosTile() == tiles.at(i)->GetPosition() && ghosts.at(j)->CanBeAtacket())
								{
									ghosts.at(j)->SwitchAtacked();
								}
							}



						}
						
							
							
					}
						
					else
					{
						if(tiles.at(i)->IsInside(player->GetWorldPosition()))
						{
							ghosts.at(j)->SetPathTo(tiles.at(i)->GetPosition());
							player->SetPosTile(tiles.at(i)->GetPosition());
							
						}
							
					}
				}
				
				else
				{
					ghosts.at(j)->SetPosition(ghstart->GetWorldPosition());
					ghosts.at(j)->releaseTime = 0.0f;

				}
			}
		}
		if(player->WasAttacked())
		{
			if(playerPunchedTimer > 1.2f)
			{
				numOfLife--;
				player->SwitchWasAttacked();
				player->SetPosition(pmstart->GetWorldPosition());
				playerPunchedTimer = 0.0f;
				

			}
		}
	}
	for(unsigned int i = 0; i < obsts.size(); i++)
	{
		if(CheckForColiding(player, obsts.at(i)))
		{
			Colision(player, obsts.at(i));
			break;
		}
		for (unsigned int j = 0; j < ghosts.size(); j++)
		{
			if(CheckForColiding(ghosts.at(j), obsts.at(i)))
			{
				Colision(ghosts.at(j), obsts.at(i));
			}
		}
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
				if(eatTimer>=0.35f)
				{
					eatTimer = 0.0f;
					hge->Effect_Play(wakaSnd);
				}
				
				foods.at(i)->EatFood();
				eatenFood++;
			}
		}
	}
	for(unsigned int i = 0; i < hFoods.size(); i++)
	{
		if(!hFoods.at(i)->IsEaten())
		{
			hFoods.at(i)->Update(dt);
			if(CheckForColiding(player, hFoods.at(i)))
			{
				hFoods.at(i)->EatFood();
				eatenFood++;
				if(player->CanBeAtacket())
				{
					player->SwitchAtacked();
					hge->Effect_Play(eatHFoodSnd);
				}
				attackTimer = 0.0f;
				
			}
		}
	}
	if(eatenFood == foods.size() + hFoods.size())
	{
		states->push(new WinMenu(states, hge));
	}
	if(numOfLife == 0)
	{
		states->push(new GameOver(states, hge));
	}
	for(unsigned int i = 0; i < ghosts.size(); i++)
	{
		if(ghosts.at(i)->releaseTime <= ReleaseTimer)
		{
			ghosts.at(i)->releaseTime += dt;
			break;
		}
		
	}
	for(unsigned int i = 0; i < ghosts.size(); i++)
	{
		if(ghosts.at(i)->releaseTime >= ReleaseTimer)
		{
			UpdateEnemies(ghosts.at(i));
			ghosts.at(i)->Update(dt);
			if(attackTimer < 7.0f && !ghosts.at(i)->CanBeAtacket() && !ghosts.at(i)->WasAttacked())
			{
				ghosts.at(i)->SwitchAtacked();
			}
			if(attackTimer > 7.0f && !ghosts.at(i)->CanBeAtacket() && !ghosts.at(i)->WasAttacked())
			{
				if(ghosts.at(i)->IsColiding(player->Rectangle()))
				{
					playerPunchedTimer = 0.0f;
					player->SwitchWasAttacked();
					hge->Effect_Play(deathSnd);
				}
			}
			else if (ghosts.at(i)->CanBeAtacket())
			{
				if(ghosts.at(i)->IsColiding(player->Rectangle()))
				{
					if(!ghosts.at(i)->WasAttacked())
					{
						
						hge->Effect_Play(eatGhostSnd);
						ghosts.at(i)->SwitchWasAtacked();
					}
					
				}
			}
				
		}
		
	}
	if(!player->CanBeAtacket() && attackTimer > 7.0f)
	{
		player->SwitchAtacked();
	}
	if(beginTimer > 4.0f&& sirenTimer >= 1.58f)
	{
		sirenTimer = 0.0f;
		hge->Effect_Play(sirenSnd);
	}
	player->Update(dt);
	beginTimer += dt;
	attackTimer += dt;
	sirenTimer += dt;
	playerPunchedTimer += dt;
	eatTimer += dt;
}
void GameState::Render()
{
	
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
	for(unsigned int i = 0; i <hFoods.size(); i++)
	{
		if(!hFoods.at(i)->IsEaten())
		{
			hFoods.at(i)->Render();
		}
	}
	// rendering enemies
	for(unsigned int i = 0; i < ghosts.size(); i++)
	{
		ghosts.at(i)->Render();
		
	}
	// rendering player
	player->Render();
	fnt->printf(originX + (750.0f / 2.0f) * scaleX, originY - (300.0f / 2.0f) * scaleY, HGETEXT_RIGHT, "NUM\nOF\nLIFE:");
	std::ostringstream ss;
    ss << numOfLife;
	fnt->printf(originX + (750.0f / 2.0f) * scaleX, originY - (140.0f / 2.0f) * scaleY, HGETEXT_RIGHT, ss.str().c_str());
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
	// Input to back to main menu
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		states->push(new GamePause(states, hge));
	};
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		EndState();
	};

	player->SetDirection(dir);

}
void GameState::FreeResources()
{
	delete player;
	delete fnt;
	delete mapManager;
	while(!mapItems.empty())
	{
		delete mapItems.back();
		mapItems.pop_back();
	}
	hge->Effect_Free(beginSnd);
	hge->Effect_Free(sirenSnd);
	hge->Effect_Free(wakaSnd);
	hge->Effect_Free(deathSnd);
	hge->Effect_Free(eatHFoodSnd);
	hge->Effect_Free(eatGhostSnd);
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