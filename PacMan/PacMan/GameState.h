#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PacMan.h"

class GameState : public State
{
public:
	GameState();
	void LoadResources(HGE *hge) override;
	//Update
	bool Update(HGE *hge, const float dt) override;
	//Render
	void Render(HGE *hge) override;
	
	void UpdateInput(HGE *hge, const float dt) override;
	void EndState() override{};
	void FreeResources(HGE *hge);
	virtual ~GameState();
private:
	static bool isLoadedResources;
	static PacMan player;

};

#endif