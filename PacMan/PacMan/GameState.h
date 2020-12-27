#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PacMan.h"
#include "MainMenu.h"

class GameState : public State
{
public:
	GameState(std::stack<State*>* states_in);
	void LoadResources(HGE *hge) override;
	//Update
	void Update(HGE *hge, const float& dt) override;
	//Render
	void Render(HGE *hge) override;
	void UpdateInput(HGE *hge, const float& dt) override;
	void FreeResources(HGE *hge) override;
	virtual ~GameState();
private:
	static bool isLoadedResources;
	// Player variable
	static PacMan player;
};

#endif