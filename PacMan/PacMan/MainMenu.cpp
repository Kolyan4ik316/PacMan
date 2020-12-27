#include "MainMenu.h"
MenuManager MainMenu::manager = MenuManager();
MainMenu::MainMenu(std::stack<State*>* states_in) : State(states_in)
{
}
bool MainMenu::Update(HGE* hge, const float& dt)
{
	UpdateInput(hge, dt);
	return false;
}
void MainMenu::Render(HGE* hge)
{
	hge->Gfx_BeginScene();

	// Clear screen with black color
	hge->Gfx_Clear(0);
	
	// Render quads here. This time just
	// one of them will serve our needs.

	// End rendering and update the screen
	hge->Gfx_EndScene();
}
void MainMenu::UpdateInput(HGE* hge, const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_SPACE))
	{
		states->push(new GameState(states));
	};
}
MainMenu::~MainMenu()
{
}