#include "Game.h"
HGE *Game::hge					= 0;
//Game::CurrentState Game::currState = Game::CurrentState::mainMenu;
int Game::screenWidth = 800;
int Game::screenHeight = 600;
bool Game::windowed = true;;
std::string Game::nameOfWindow = "PacMan";
std::stack<State*> Game::states = std::stack<State*>();
Game::Game()
{
	InitWindow();
	//InitStates();
	

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
	states.push(new MainMenu(&states, hge));
}
void Game::ChangePreference()
{

	// Set the window title
	hge->System_SetState(HGE_TITLE, nameOfWindow.c_str());
	
	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, windowed);
	hge->System_SetState(HGE_SCREENWIDTH, screenWidth);
	hge->System_SetState(HGE_SCREENHEIGHT, screenHeight);
}

void Game::Run()
{
	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, Update);
	hge->System_SetState(HGE_RENDERFUNC, Render);

	ChangePreference();
	// Don't use BASS for sound
	//hge->System_SetState(HGE_USESOUND, true);
	
	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	
	if(hge->System_Initiate())
	{
		InitStates();
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
	//Cleaning states
	// Bug is fixed;
	QuitFromApplication();

	// Restore video mode and free
	// all allocated resources
	hge->System_Shutdown();

	
	
	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();
	
	
}
void Game::QuitFromApplication()
{
	while(!states.empty())
	{
		states.top()->FreeResources();
		delete states.top();
		states.pop();
	}
}
bool Game::Update()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if(!states.empty())
	{
		states.top()->Update(hge->Timer_GetDelta());
		if(states.top()->GetQuit())
		{
			//states.top()->EndState();
			delete states.top();
			states.pop();
		}
		return false;
	}
	else
	{
		return true;
	}
	
	// Continue execution
	//return false;
}
bool Game::Render()
{
	if (!states.empty())
	{
		hge->Gfx_BeginScene();

		// Clear screen with black color
		hge->Gfx_Clear(0);

		states.top()->Render();

		// End rendering and update the screen
		hge->Gfx_EndScene();
	}
	// RenderFunc should always return false
	return false;
}
Game::~Game()
{
}