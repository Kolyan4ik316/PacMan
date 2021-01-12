#ifndef WINMENU_H
#define WINMENU_H
#include "Menu.h"
class WinMenu : public Menu
{
public:
	WinMenu(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;

	virtual ~WinMenu();
};
#endif