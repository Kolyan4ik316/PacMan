#ifndef MAINMENU_H
#define MAINMENU_H
//#include "State.h"
#include "GameState.h"
#include "Button.h"
#include "Menu.h"
#include "Options.h"
class MainMenu : public Menu
{
public:
	MainMenu(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;
	//void EndState() override{};
	virtual ~MainMenu();
private:
};


#endif