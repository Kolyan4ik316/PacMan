#include "DiffOption.h"
DiffOption::DiffOption(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{
	gui->AddCtrl(new Button(1,fnt, snd, originX, button1, 0.0f, "Easy"));
	gui->AddCtrl(new Button(2,fnt, snd, originX, button2, 0.1f, "Normal"));
	gui->AddCtrl(new Button(3,fnt, snd, originX, button3, 0.1f, "Hard"));
	gui->AddCtrl(new Button(4,fnt, snd, originX, button4, 0.1f, "Return to Options"));
	gui->AddCtrl(new Button(5,fnt, snd, originX, button5, 0.2f, "Return to Main Menu"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(2);
	gui->Enter();
}
void DiffOption::Update(const float& dt)
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
				difficult = State::Difficult::Easy;
				break;
			case 2:
				gui->Enter();
				difficult = State::Difficult::Normal;
				break;
			case 3:
				gui->Enter();
				difficult = State::Difficult::Hard;
				break;
			case 4:
				gui->Enter();
				EndState();
				break;

			case 5: 
				gui->Enter();
				toMainMenu = true;
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void DiffOption::Render()
{
	const float posX = originX / scaleX - 1280.0f / 2.0f;
	const float posY = originY / scaleY - 720.0f / 2.0f;
	bgSpr->RenderEx(posX , posY, 0.0f, scaleX, scaleY); 
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(originX, originY - 200.0f, HGETEXT_CENTER, "Choose difficult");
}
void DiffOption::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		gui->Leave();
		EndState();
	};
}
DiffOption::~DiffOption()
{
	//FreeResources();
	//delete gui;
	//delete manager;
	//manager = NULL;
}