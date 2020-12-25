#include "Game.h"
HGE *Game::hge					= 0;

int Game::screenWidth = 800;
int Game::screenHeight = 600;
bool Game::windowed = true;;
std::stack<State*> Game::states = std::stack<State*>();
Game::Game()
{
	InitWindow();
	InitStates();
	
	//screenWidth = 800;
	//screenHeight = 600;
	//windowed = true;
	

	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = hgeCreate(HGE_VERSION);
}
void Game::InitWindow()
{
	std::fstream fs;
	
}
void Game::InitStates()
{
	states.push(new GameState());
}

void Game::Run()
{
	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, Update);
	hge->System_SetState(HGE_RENDERFUNC, Render);

	// Set the window title
	hge->System_SetState(HGE_TITLE, "PacMan");
	
	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, windowed);
	hge->System_SetState(HGE_SCREENWIDTH, screenWidth);
	hge->System_SetState(HGE_SCREENHEIGHT, screenHeight);
	// Don't use BASS for sound
	//hge->System_SetState(HGE_USESOUND, true);
	
	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	
	if(hge->System_Initiate())
	{
		//states.top()->LoadRecources(hge);
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		hge->System_Start();
	}
	else
	{	
		// If HGE initialization failed show error message
		throw(std::exception(hge->System_GetErrorMessage()));
	}

	

	
	
}
bool Game::Update()
{
	// Now ESC has been pressed or the user
	// has closed the window by other means.
	// By returning "true" we tell HGE
	// to stop running the application.
	
	return states.top()->Update(hge, hge->Timer_GetDelta());
	// Continue execution
	//return false;
}
bool Game::Render()
{
	states.top()->Render(hge);
	// RenderFunc should always return false
	return false;
}
Game::~Game()
{
	for(unsigned int i = 0; i < states.size(); i++)
	{	
		states.top()->FreeResources(hge);
		delete states.top();
		states.pop();
	}
	// Restore video mode and free
	// all allocated resources
	hge->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();
	
}