#include "GamePause.h"
GamePause::GamePause(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{

	gui->AddCtrl(new Button(1,fnt, snd, originX, button1, 0.0f, "Continue"));
	gui->AddCtrl(new Button(2,fnt, snd, originX, button2, 0.1f, "Main Menu"));
	gui->AddCtrl(new Button(3,fnt, snd, originX, button3, 0.2f, "Exit"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}
void GamePause::Update(const float& dt)
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
				EndState();
				break;
			case 2:
				toMainMenu = true;
				break;
			case 3:
				closeGame = true;
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void GamePause::Render()
{
	const float posX = originX / scaleX - 1280.0f / 2.0f;
	const float posY = originY / scaleY - 720.0f / 2.0f;
	bgSpr->RenderEx(posX , posY, 0.0f, scaleX, scaleY); 
	gui->Render();
	//fnt->SetColor(0xFFFFFFFF);
	//fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
}
void GamePause::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		gui->Leave();
		EndState();
	};
}
GamePause::~GamePause()
{

}