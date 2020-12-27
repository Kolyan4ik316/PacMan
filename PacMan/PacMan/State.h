#ifndef STATE_H
#define STATE_H
#include "EntryHeader.h"
class State
{
public:
	//Ctor(takes paramaters, i'm gonna add more paramaters later)
	State(std::stack<State*>* states_in);
	//Update
	virtual void Update(HGE *hge, const float& dt) = 0;
	//Render
	virtual void Render(HGE *hge) = 0;
	// Updating key states, mouse state
	virtual void UpdateInput(HGE *hge, const float& dt) = 0;
	// function calling when we need to quit
	virtual void EndState()
	{
		quit = true;
	}
	// Function for loading resources and releasing them
	virtual void LoadResources(HGE *hge) = 0;
	virtual void FreeResources(HGE *hge) = 0;
	
	// Returning if we quit from state
	const bool& GetQuit() const
	{
		return quit;
	}
	//Dtor (need to be virtual for base class, for preventing memory leak)
	virtual ~State(){};
protected:
	// variable for quiting
	bool quit;
	// Pointer to stack of pointer of states
	// we can managing of states by using him
	std::stack<State*>* states;
};
//
#endif