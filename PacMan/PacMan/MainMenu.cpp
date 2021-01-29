#include "MainMenu.h"
MainMenu::MainMenu(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{

	gui->AddCtrl(new Button(1,fnt, snd, originX, originY - 100.0f, 0.0f, "Play"));
	gui->AddCtrl(new Button(2,fnt, snd, originX, originY - 60.0f, 0.1f, "Options"));
	gui->AddCtrl(new Button(3,fnt, snd, originX, originY - 20.0f, 0.2f, "Instructions"));
	gui->AddCtrl(new Button(4,fnt, snd, originX, originY + 20.0f, 0.3f, "Credits"));
	gui->AddCtrl(new Button(5,fnt, snd, originX, originY + 60.0f, 0.4f, "Exit"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}
void MainMenu::Update(const float& dt)
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
				states->push(new GameState(states, hge));
				break;
			case 2:
				gui->Enter();
				states->push(new Options(states, hge));
				break;
			case 3:
				gui->Enter();
				gui->SetFocus(1);
				break;
			case 4:
				gui->Enter();
				states->push(new Credits(states, hge));
				break;

			case 5: 
				gui->Enter();
				EndState();
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void MainMenu::Render()
{
	const float posX = originX / scaleX - 1280.0f / 2.0f;
	const float posY = originY / scaleY - 720.0f / 2.0f;
	bgSpr->RenderEx(posX , posY, 0.0f, scaleX, scaleY); 
	gui->Render();
	//fnt->SetColor(0xFFFFFFFF);
	//fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
}
void MainMenu::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		gui->Leave();
		EndState();
	};
}
MainMenu::~MainMenu()
{
	//FreeResources();
	//delete gui;
	//delete manager;
	//manager = NULL;
}