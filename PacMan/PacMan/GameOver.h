#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "Menu.h"
class GameOver : public Menu
{
public:
	GameOver(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;

	virtual ~GameOver();
};
#endif