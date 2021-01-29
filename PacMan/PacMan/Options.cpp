#include "Options.h"
Options::Options(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{

	gui->AddCtrl(new Button(1,fnt, snd, originX, button1, 0.0f, "Resolution"));
	gui->AddCtrl(new Button(2,fnt, snd, originX, button2, 0.1f, "Difficult"));
	gui->AddCtrl(new Button(3,fnt, snd, originX, button5, 0.3f, "Return to MainMenu"));
	gui->AddCtrl(new Button(4,fnt, snd, originX, button6, 0.4f, "Exit"));

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
				gui->Enter();
				states->push(new DiffOption(states, hge));
				break;
			case 3:
				gui->Enter();
				EndState();
				break;
			case 4: 
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
	const float posX = originX / scaleX - 1280.0f / 2.0f;
	const float posY = originY / scaleY - 720.0f / 2.0f;
	bgSpr->RenderEx(posX , posY, 0.0f, scaleX, scaleY); 
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