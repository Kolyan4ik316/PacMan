#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PacMan.h"
#include "MainMenu.h"
#include "Ghost.h"
#include "Obstacles.h"

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
	static bool isLoadedResources;
	// Player variable
	PacMan* player;
	Ghost* ghost;
	Obstacles* obst;

};

#endif