#ifndef DIFFOPTION_H
#define DIFFOPTION_H
#include "Menu.h"
class DiffOption : public Menu
{
public:
	DiffOption(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;
	virtual ~DiffOption();
private:
	void LoadDiff();
};
#endif