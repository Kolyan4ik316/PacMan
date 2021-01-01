#ifndef STATE_H
#define STATE_H
#include "EntryHeader.h"
class State
{
public:
	//Ctor(takes paramaters, i'm gonna add more paramaters later)
	State(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) = 0;
	//Render
	virtual void Render() = 0;
	// Updating key states, mouse state
	virtual void UpdateInput(const float& dt) = 0;
	// function calling when we need to quit
	virtual void EndState()
	{
		quit = true;
	}
	// Function for loading resources and releasing them
	virtual void LoadResources() = 0;
	virtual void FreeResources() = 0;
	virtual void SetReoslution(const std::string& resolution);
	
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
	HGE* hge;
	static int screenWidth;
	static int screenHeight;
	
	static float originX;
	static float originY;

	static float scaleX;
	static float scaleY;

};
//
#endif