#include "Credits.h"
Credits::Credits(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{
	gui->AddCtrl(new Button(1, fnt, snd, originX, button6, 0.4f, "Return to Main Menu"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}
void Credits::Update(const float& dt)
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
				EndState();
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void Credits::Render()
{
	const float posX = originX / scaleX - 1280.0f / 2.0f;
	const float posY = originY / scaleY - 720.0f / 2.0f;
	bgSpr->RenderEx(posX , posY, 0.0f, scaleX, scaleY); 
	gui->Render();
	fnt->printf(originX, originY - 200.0f, HGETEXT_CENTER, "Game was created by Kolyan4ik316\ngithub.com/kolyan4ik316");
}
void Credits::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		gui->Leave();
		EndState();
	};
}
Credits::~Credits()
{
}