#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PacMan.h"
#include "MainMenu.h"
#include "Ghost.h"
#include "Obstacles.h"
#include "Tiles.h"

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
	static float Distance(Tiles* a, Tiles* b);
	static float Heuristic(Tiles* a, Tiles* b);
	void SolveA_Star();
	static bool LessfGlobalGoal(const Tiles* lhs, const Tiles* rhs)
	{
		return lhs->fGlobalGoal < rhs->fGlobalGoal;
	}
	static bool LessfLocalGoal(const Tiles* lhs, const Tiles* rhs)
	{
		return lhs->fLocalGoal< rhs->fLocalGoal;
	}
	void UpdateEnemies();
	// Player variable
	PacMan* player;
	Ghost* ghost;
	Obstacles* obst;
	std::vector<Tiles*> tiles;
	unsigned int nMapWidth;
	unsigned int nMapHeight;
};

#endif