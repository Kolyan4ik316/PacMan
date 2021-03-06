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
	
	static void ChangePreference();
	static void QuitFromApplication();
	~Game();	
private:
	// For initialize window attributes
	void InitWindow();
	// For initialize state of game
	void InitStates();
	// For initialize difficults
	void InitDiff();

private:
	// Container of states
	static std::stack<State*> states;
	// Main pointer of HGE class
	static HGE *hge;
private:
	//Window attributes
	static int screenWidth;
	static int screenHeight;
	static bool windowed;
	static std::string nameOfWindow;
	static std::string windowMode;
private:
};


#endif