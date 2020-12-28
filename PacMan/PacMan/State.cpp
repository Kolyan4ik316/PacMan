#include "State.h"
State::State(std::stack<State*>* states_in, HGE* hge_in) 
	: 
	states(states_in),
	hge(hge_in)
{
	
}