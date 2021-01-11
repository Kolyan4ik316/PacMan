#include "Options.h"
Options::Options(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{

	gui->AddCtrl(new Button(1,fnt, snd, originX, originY - 100.0f, 0.0f, "Resolution"));
	gui->AddCtrl(new Button(2,fnt, snd, originX, originY - 60.0f, 0.1f, "Difficult"));
	gui->AddCtrl(new Button(4,fnt, snd, originX, originY + 20.0f, 0.3f, "Return to MainMenu"));
	gui->AddCtrl(new Button(5,fnt, snd, originX, originY + 60.0f, 0.4f, "Exit"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}
void Options::Update(const float& dt)
{
	int id;
	static int lastid=0;

	
	// We update the GUI and take an action if
	// one of the menu items was selected
	id=gui->Update(dt);
	if(id == -1)
	{
		switch(lastid)
		{
			case 1:
				gui->Enter();
				states->push(new ResolutionOption(states, hge));
				break;
			case 2:
			case 3:
			case 4:
				gui->Enter();
				EndState();
				break;

			case 5: 
				gui->Enter();
				closeGame = true;
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void Options::Render()
{
	hge->Gfx_RenderQuad(&quad);
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	//fnt->printf(originX, originY - 200.0f, HGETEXT_CENTER, "Choose difficult");
}
void Options::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		gui->Leave();
		EndState();
	};
}
Options::~Options()
{
	//FreeResources();
	//delete gui;
	//delete manager;
	//manager = NULL;
}