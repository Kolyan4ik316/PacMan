#ifndef GAMEPAUSE_H
#define GAMEPAUSE_H
#include "Menu.h"
class GamePause : public Menu
{
public:
	GamePause(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;

	virtual ~GamePause();
};
#endif