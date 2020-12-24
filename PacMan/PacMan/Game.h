#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "GameState.h"

class Game
{
public:
	Game();
	//Main function
	void Run();
	//Update
	static bool Update();
	//Render
	static bool Render();

	void QuitFromApplication();
	~Game();
private:
	void InitWindow();
	void InitStates();
private:
	std::stack<State*> states;
	static HGE *hge;
};


#endif