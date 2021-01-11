#ifndef OPTIONS_H
#define OPTIONS_H
#include "Menu.h"
#include "ResolutionOption.h"
#include "DiffOption.h"
class Options : public Menu
{
public:
	Options();
	Options(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;
	//void EndState() override{};
	virtual ~Options();
};
#endif