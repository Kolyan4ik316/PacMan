#ifndef MAINMENU_H
#define MAINMENU_H
//#include "State.h"
#include "GameState.h"
#include "MenuManager.h"
class MainMenu : public State
{
public:
	MainMenu(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	void Update(const float& dt) override;
	//Render
	void Render() override;
	
	void UpdateInput(const float& dt) override;
	//void EndState() override{};

	virtual void LoadResources() override{};
	virtual void FreeResources() override{};
	virtual ~MainMenu();
private:
	//Will managing our menu
	static MenuManager manager;
};


#endif