#include "State.h"
//bool State::quit = false;
State::State(std::stack<State*>* states_in, HGE* hge_in) 
	: 
	states(states_in),
	hge(hge_in)
{
	
}