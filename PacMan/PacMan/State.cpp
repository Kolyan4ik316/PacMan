#include "State.h"
State::State(std::stack<State*>* states_in, HGE* hge_in) 
	: 
	states(states_in),
	hge(hge_in)
{
	screenWidth =  hge->System_GetState(HGE_SCREENWIDTH);
	screenHeight =  hge->System_GetState(HGE_SCREENHEIGHT);
	originX = float(screenWidth / 2);
	originY = float(screenHeight / 2);
}