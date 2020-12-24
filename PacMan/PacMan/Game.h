#ifndef GAME_H
#define GAME_H
#define HGE_DIRECTX_VER 9
#include <hge.h>
#include <exception>
//Linking lib
#pragma comment( lib, "hge.lib" )

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
	~Game();
private:
	void InitWindow();
	void InitStates();
private:
	static HGE *hge;
};


#endif