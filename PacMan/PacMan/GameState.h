#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"

class GameState : public State
{
public:
	GameState();

	//Update
	bool Update() override{return false;};
	//Render
	bool Render() override{return false;};
	
	void UpdateInput(const float& dt) override{};
	void EndState() override{};

	virtual ~GameState();
};

#endif