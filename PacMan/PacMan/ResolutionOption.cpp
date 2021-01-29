#include "ResolutionOption.h"
ResolutionOption::ResolutionOption(std::stack<State*>* states_in, HGE* hge_in) : Menu(states_in, hge_in)
{
	toMainMenu = false;
	closeGame = false;
	isWindowed =  hge->System_GetState(HGE_WINDOWED);
	tempWidth = screenWidth;
	tempHeight = screenHeight;
	tempRes = resolut;
	gui->AddCtrl(new Button(1,fnt, snd, originX, button1, 0.0f, "800 x 600 | 4:3"));
	gui->AddCtrl(new Button(2,fnt, snd, originX, button2, 0.1f, "1280 x 720 | 16:9"));
	gui->AddCtrl(new Button(3,fnt, snd, originX, button3, 0.1f, "1600 x 900 | 16:9"));
	gui->AddCtrl(new Button(4,fnt, snd, originX, button4, 0.1f, "1600 x 1000 | 16:10"));
	gui->AddCtrl(new Button(5,fnt, snd, originX, button5, 0.2f, "1920 x 1080 | 16:9"));
	gui->AddCtrl(new Button(6,fnt, snd, originX, button6, 0.3f, "Windowed"));
	gui->AddCtrl(new Button(7,fnt, snd, originX, button7, 0.3f, "Return to Options"));
	gui->AddCtrl(new Button(8,fnt, snd, originX, button8, 0.3f, "Exit"));

	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(7);
	gui->Enter();
}
void ResolutionOption::Update(const float& dt)
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
				SetPreference(800, 600, "4:3");
				ChangeResolution();
				break;
			case 2:
				gui->Enter();
				SetPreference(1280, 720, "16:9");
				ChangeResolution();
				break;
			case 3:
				gui->Enter();
				SetPreference(1600, 900, "16:9");
				ChangeResolution();
				break;
			case 4:
				gui->Enter();
				SetPreference(1600, 1000, "16:10");
				ChangeResolution();
				break;
			case 5:
				gui->Enter();
				SetPreference(1920, 1080, "16:9");
				ChangeResolution();
				break;
			case 6:
				gui->Enter();
				isWindowed = !isWindowed;
				SetPreference(tempWidth, tempHeight, tempRes);
				ChangeResolution();
				break;
			case 7:
				gui->Enter();
				EndState();
				break;
			case 8:
				gui->Enter();
				closeGame = true;
				break;
		}
	}
	else if(id) { lastid=id; gui->Leave(); }
	UpdateBG(dt);


	UpdateInput(dt);
}
void ResolutionOption::SetPreference(const int& width, const int& height, const std::string& resol)
{
	tempWindowed = isWindowed;
	tempWidth = width;
	tempHeight = height;
	tempRes = resol;
}
void ResolutionOption::ChangeResolution()
{
	std::string path = "Configs\\window.ini";
	std::ofstream ofs;
	ofs.open(path.c_str());
	if(ofs.is_open())
	{
		//Writing variables
		ofs<<"[Window_Width]\n"
			<<tempWidth<<"\n"
			<<"[Window_Height]\n"
			<<tempHeight<<"\n"
			<<"[Windowed]\n"
			<<tempWindowed<<"\n"
			<<"[Resolution_Mode]\n"
			<<tempRes.c_str()<<"\n"
			<<"[Window_Name]\n"
			<<"PacMan"<<"\n";
	}
	else
	{
		// if can't create
		throw(std::exception("Unknown error while writing to file window.ini"));
	}
	ofs.close();
}
void ResolutionOption::Render()
{
	const float posX = originX / scaleX - 1280.0f / 2.0f;
	const float posY = originY / scaleY - 720.0f / 2.0f;
	bgSpr->RenderEx(posX , posY, 0.0f, scaleX, scaleY); 
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(originX, originY - 200.0f, HGETEXT_CENTER, "Resolution will be changed \nafter resatrting the game");
}
void ResolutionOption::UpdateInput(const float& dt)
{
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		gui->Leave();
		EndState();
	};
}
ResolutionOption::~ResolutionOption()
{

}