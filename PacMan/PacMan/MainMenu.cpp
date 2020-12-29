#include "MainMenu.h"
//MenuManager MainMenu::manager = MenuManager(hge);
MainMenu::MainMenu(std::stack<State*>* states_in, HGE* hge_in) : State(states_in, hge_in)
{
	manager = new MenuManager(hge_in);
	quit = false;
}
void MainMenu::Update(const float& dt)
{
	UpdateInput(dt);
}
void MainMenu::Render()
{
}
void MainMenu::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_SPACE))
	{
		states->push(new GameState(states, hge));
	};
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		EndState();
	};
}
MainMenu::~MainMenu()
{
	delete manager;
	manager = NULL;
}