#include "WinMenu.h"
WinMenu::WinMenu(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{
	gui->AddCtrl(new Button(1, fnt, snd, originX, originY + 60.0f, 0.4f, "Return to Main Menu"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}
void WinMenu::Update(const float& dt)
{
	int id;
	static int lastid=0;
	id=gui->Update(dt);
	if(id == -1)
	{
		switch(lastid)
		{
			case 1:
				gui->Enter();
				toMainMenu = true;
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void WinMenu::Render()
{
	hge->Gfx_RenderQuad(&quad);
	gui->Render();
	fnt->printf(originX, originY - 200.0f, HGETEXT_CENTER, "Congratulation, you've win!!!");
}
void WinMenu::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		gui->Leave();
		toMainMenu = true;
	};
}
WinMenu::~WinMenu()
{
}