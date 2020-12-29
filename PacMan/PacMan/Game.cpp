#include "Game.h"
HGE *Game::hge					= NULL;
int Game::screenWidth = 800;
int Game::screenHeight = 600;
bool Game::windowed = true;;
std::string Game::nameOfWindow = "PacMan";
std::stack<State*> Game::states = std::stack<State*>();
Game::Game()
{
	InitWindow();

	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = hgeCreate(HGE_VERSION);
}
void Game::InitWindow()
{
	std::string path = "Configs\\window.ini";
	std::ifstream ifs;
	ifs.open(path.c_str());
	// if file is already exist
	if(ifs.is_open())
	{
		//Reading variables
		ifs>> nameOfWindow
			>>screenWidth
			>>screenHeight
			>>windowed;
	}
	else
	{
		//if not exist creating new file in same path
		std::ofstream ofs;
		ofs.open(path.c_str());
		if(ofs.is_open())
		{
			//Writing variables
			ofs<<nameOfWindow.c_str()<<"\n"<<screenWidth<<"\n"<<screenHeight<<"\n"<<windowed<<"\n";
		}
		else
		{
			// if can't create
			throw(std::exception("Unknown error while writing to file window.ini"));
		}
		ofs.close();
	}
	ifs.close();
	
}
void Game::InitStates()
{
	// Pushing main menu
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
	hge->System_SetState(HGE_SCREENBPP, 32);
}

void Game::Run()
{
	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, Update);
	hge->System_SetState(HGE_RENDERFUNC, Render);

	ChangePreference();
	
	
	if(hge->System_Initiate())
	{
		// Creating main menu
		InitStates();
		// Starting programm itself
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
	// cleaning our states pointers
	// for (unsgned int i = 0; i< states.size(); i++) not erasing first element
	while(!states.empty())
	{
		states.top()->FreeResources();
		delete states.top();
		states.pop();
	}
}
bool Game::Update()
{
	// if container have states game will updating
	if(!states.empty())
	{
		//We are gonna to use timer from a lib, becouse in this version of c++
		//chrono is not exist :)
		states.top()->Update(hge->Timer_GetDelta());
		if(states.top()->GetQuit())
		{
			delete states.top();
			states.pop();
		}
		// Continue execution
		return false;
	}
	else
	{
		// By returning "true" we tell HGE
		// to stop running the application.
		return true;
	}
}
bool Game::Render()
{
	// if container have states game will rendering
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