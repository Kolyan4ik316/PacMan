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
	void UpdateEnemies();
	// Player variable
	PacMan* player;
	Ghost* ghost;
	Obstacles* obst;
	std::vector<Tiles*> tiles;
	PathFinder* pathfinder;
	unsigned int nMapWidth;
	unsigned int nMapHeight;
	Food* food;
	HolyFood* holyFood;
};

#endif