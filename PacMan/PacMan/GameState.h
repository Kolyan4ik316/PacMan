#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PacMan.h"
#include "MainMenu.h"
#include "Ghost.h"
#include "Obstacles.h"
#include "Tiles.h"
#include "PathFinder.h"
#include "Food.h"
#include "HolyFood.h"
#include "GamePause.h"
#include "MapManager.h"

class GameState : public State
{
public:
	GameState(std::stack<State*>* states_in, HGE* hge_in);
	void LoadResources() override;
	//Update
	void Update(const float& dt) override;
	//Render
	void Render() override;
	void UpdateInput(const float& dt) override;
	void FreeResources() override;
	virtual ~GameState();
private:
	void UpdateEnemies(Ghost* ghost);
	const bool CheckForColiding(DynamicEntity* checker, Entity* colisior) const;
	void Colision(DynamicEntity* checker, Entity* colisior);
	// Player variable
	PacMan* player;
	std::vector<Tiles*> tiles;
	PathFinder* pathfinder;
	unsigned int nMapWidth;
	unsigned int nMapHeight;
	MapManager* mapManager;
	std::vector<Entity*> mapItems;
	std::vector<Obstacles*> obsts;
	std::vector<Food*> foods;
	int eatenFood;
	int numOfTry;
};

#endif