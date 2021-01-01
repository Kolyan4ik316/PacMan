#include "State.h"
int State::screenWidth = 0;
int State::screenHeight = 0;
float State::originX = 0.0f;
float State::originY = 0.0f;
float State::scaleX = 0.0f;
float State::scaleY = 0.0f;
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
void State::SetReoslution(const std::string& resolution)
{
	if(resolution.compare("4:3") == 0)
	{
		for(int x = 0; x <screenWidth; x += 4)
		{
			scaleX += 0.005f;
		
		}
		
		for(int y = 0; y <screenHeight; y += 3)
		{
			scaleY += 0.005f;
		}
	}
	else if(resolution.compare("16:9") == 0)
	{
		for(int x = 0; x <screenWidth; x += 16)
		{
			scaleX += 0.01f;
		
		}
		
		for(int y = 0; y <screenHeight; y += 9)
		{
			scaleY += 0.01f;
		}
	}
	else if(resolution.compare("16:10") == 0)
	{
		for(int x = 0; x <screenWidth; x += 16)
		{
			scaleX += 0.01f;
		
		}
		
		for(int y = 0; y <screenHeight; y += 10)
		{
			scaleY += 0.01f;
		}
	}
	else
	{
		std::string error = std::string("Couldn't use your resolution " + resolution + ".\nPlease try to use 4:3, or 16:9, or 16:10");
		throw(std::exception(error.c_str()));
	}
}