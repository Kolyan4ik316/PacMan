#include "MainMenu.h"
MenuManager MainMenu::manager = MenuManager();
MainMenu::MainMenu(std::stack<State*>* states_in) : State(states_in)
{
	quit = false;
}
void MainMenu::Update(HGE* hge, const float& dt)
{
	UpdateInput(hge, dt);
}
void MainMenu::Render(HGE* hge)
{
}
void MainMenu::UpdateInput(HGE* hge, const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_SPACE))
	{
		states->push(new GameState(states));
	};
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		EndState();
	};
}
MainMenu::~MainMenu()
{
}