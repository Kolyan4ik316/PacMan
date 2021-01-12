#include "Game.h"
HGE *Game::hge					= NULL;
int Game::screenWidth = 800;
int Game::screenHeight = 600;
bool Game::windowed = true;;
std::string Game::nameOfWindow = "PacMan";
std::string Game::windowMode = "4:3";
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
		std::string tempStr;
		while(!ifs.eof())
		{
			ifs>> tempStr;
			if(tempStr.compare("[Window_Width]") == 0)
			{
				ifs>>screenWidth;
			}
			if(tempStr.compare("[Window_Height]") == 0)
			{
				ifs>>screenHeight;
			}
			if(tempStr.compare("[Windowed]") == 0)
			{
				ifs>>windowed;
			}
			if(tempStr.compare("[Resolution_Mode]") == 0)
			{
				ifs>>windowMode;
			}
			if(tempStr.compare("[Window_Name]") == 0)
			{
				nameOfWindow.clear();
				while(getline(ifs,tempStr))
				{
					nameOfWindow += tempStr;
				}
			}

		}
	}
	else
	{
		//if not exist creating new file in same path
		std::ofstream ofs;
		ofs.open(path.c_str());
		if(ofs.is_open())
		{
			//Writing variables
			ofs<<"[Window_Width]\n"
				<<screenWidth<<"\n"
				<<"[Window_Height]\n"
				<<screenHeight<<"\n"
				<<"[Windowed]\n"
				<<windowed<<"\n"
				<<"[Resolution_Mode]\n"
				<<windowMode.c_str()<<"\n"
				<<"[Window_Name]\n"
				<<nameOfWindow.c_str()<<"\n";
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
void Game::InitDiff()
{
	std::string path = "Configs\\difficult.ini";
	std::ifstream ifs;
	ifs.open(path.c_str());
	// if file is already exist
	if(ifs.is_open())
	{
		//Reading variables
		std::string tempStr;
		while(!ifs.eof())
		{
			ifs>> tempStr;
			if(tempStr.compare("[Easy]") == 0)
			{
				ifs>> tempStr;
				State::DiffAtributes tempAttr;
				while(!tempStr.compare("[End]") == 0)
				{
					if(tempStr.compare("[Num_of_ghosts]") == 0)
					{
						ifs>>tempAttr.num_of_ghosts;
					}
					if(tempStr.compare("[Speed_of_ghosts]") == 0)
					{
						ifs>>tempAttr.speed_of_ghosts;
					}
					if(tempStr.compare("[Release_delay]") == 0)
					{
						ifs>>tempAttr.release_delay;
					}
					if(tempStr.compare("[PacMan_speed]") == 0)
					{
						ifs>>tempAttr.pacMan_speed;
					}
					ifs>> tempStr;
				}
				states.top()->LoadDifficults(tempAttr);
			}
			if(tempStr.compare("[Normal]") == 0)
			{
				ifs>> tempStr;
				State::DiffAtributes tempAttr;
				while(!tempStr.compare("[End]") == 0)
				{
					if(tempStr.compare("[Num_of_ghosts]") == 0)
					{
						ifs>>tempAttr.num_of_ghosts;
					}
					if(tempStr.compare("[Speed_of_ghosts]") == 0)
					{
						ifs>>tempAttr.speed_of_ghosts;
					}
					if(tempStr.compare("[Release_delay]") == 0)
					{
						ifs>>tempAttr.release_delay;
					}
					if(tempStr.compare("[PacMan_speed]") == 0)
					{
						ifs>>tempAttr.pacMan_speed;
					}
					ifs>> tempStr;
				}
				states.top()->LoadDifficults(tempAttr);
			}
			if(tempStr.compare("[Hard]") == 0)
			{
				ifs>> tempStr;
				State::DiffAtributes tempAttr;
				while(!tempStr.compare("[End]") == 0)
				{
					if(tempStr.compare("[Num_of_ghosts]") == 0)
					{
						ifs>>tempAttr.num_of_ghosts;
					}
					if(tempStr.compare("[Speed_of_ghosts]") == 0)
					{
						ifs>>tempAttr.speed_of_ghosts;
					}
					if(tempStr.compare("[Release_delay]") == 0)
					{
						ifs>>tempAttr.release_delay;
					}
					if(tempStr.compare("[PacMan_speed]") == 0)
					{
						ifs>>tempAttr.pacMan_speed;
					}
					ifs>> tempStr;
				}
				states.top()->LoadDifficults(tempAttr);
				
			}

		}
	}
	else
	{
		//if not exist creating new file in same path
		std::ofstream ofs;
		ofs.open(path.c_str());
		if(ofs.is_open())
		{
			//Writing variables
			ofs<<"[Easy]\n"
				<<"[Num_of_ghosts]\n"
				<<3<<"\n"
				<<"[Speed_of_ghosts]\n"
				<<50.0<<"\n"
				<<"[Release_delay]\n"
				<<10.0<<"\n"
				<<"[PacMan_speed]\n"
				<<110.0<<"\n"
				<<"[End]\n"
				<<"[Normal]\n"
				<<"[Num_of_ghosts]\n"
				<<4<<"\n"
				<<"[Speed_of_ghosts]\n"
				<<60.0<<"\n"
				<<"[Release_delay]\n"
				<<10.0<<"\n"
				<<"[PacMan_speed]\n"
				<<100.0<<"\n"
				<<"[End]\n"
				<<"[Hard]\n"
				<<"[Num_of_ghosts]\n"
				<<5<<"\n"
				<<"[Speed_of_ghosts]\n"
				<<70.0<<"\n"
				<<"[Release_delay]\n"
				<<7.0<<"\n"
				<<"[PacMan_speed]\n"
				<<100.0<<"\n"
				<<"[End]";
		}
		else
		{
			// if can't create
			throw(std::exception("Unknown error while writing to file difficult.ini"));
		}
		ofs.close();
	}
	ifs.close();
}
void Game::InitStates()
{
	// Pushing main menu
	states.push(new MainMenu(&states, hge));
	InitDiff();
	//states.top()->SetDifficult(2);
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
		states.top()->SetReoslution(windowMode);
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
		//states.top()->FreeResources();
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
		
		if(states.top()->CloseGame())
		{
			QuitFromApplication();
			return true;
		}
		if(states.top()->ToMainMenu())
		{
			while(states.size() != 1)
			{
				delete states.top();
				states.pop();
			}
			return false;
		}

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