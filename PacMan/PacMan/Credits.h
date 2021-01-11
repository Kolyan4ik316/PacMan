#ifndef CREDITS_H
#define CREDITS_H
#include "Menu.h"
class Credits : public Menu
{
public:
	Credits(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;

	virtual ~Credits();
};
#endif