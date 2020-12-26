#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
class MainMenu : public State
{
public:
	MainMenu();
	//Update
	bool Update(HGE *hge, const float& dt) override {return false;};
	//Render
	void Render(HGE *hge) override {};
	
	void UpdateInput(HGE *hge, const float& dt) override{};
	void EndState() override{};

	virtual void LoadResources(HGE *hge) override{};
	virtual void FreeResources(HGE *hge) override{};
	virtual ~MainMenu();
private:
	//static std::list<hgeGUIText> texts;
	//static std::list<hgeGUIButton> buttons;
};

#endif