#ifndef MAINMENU_H
#define MAINMENU_H
//#include "State.h"
#include "GameState.h"
#include "MenuManager.h"
class MainMenu : public State
{
public:
	MainMenu(std::stack<State*>* states_in);
	//Update
	void Update(HGE *hge, const float& dt) override;
	//Render
	void Render(HGE *hge) override;
	
	void UpdateInput(HGE *hge, const float& dt) override;
	//void EndState() override{};

	virtual void LoadResources(HGE *hge) override{};
	virtual void FreeResources(HGE *hge) override{};
	virtual ~MainMenu();
private:
	//Will managing our menu
	static MenuManager manager;
};


#endif