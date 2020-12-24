#include "Game.h"
HGE *Game::hge					= 0;
Game::Game()
{
}
void Game::Run()
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = hgeCreate(HGE_VERSION);
	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, Update);

	// Set the window title
	hge->System_SetState(HGE_TITLE, "HGE Tutorial 01 - Minimal HGE application");
	
	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, false);

	// Don't use BASS for sound
	hge->System_SetState(HGE_USESOUND, false);

	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	if(hge->System_Initiate())
	{
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		hge->System_Start();
	}
	else
	{	
		// If HGE initialization failed show error message
		throw(std::exception(hge->System_GetErrorMessage()));
	}

	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	hge->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();
}
bool Game::Update()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;

	// Continue execution
	return false;
}
bool Game::Render()
{
	//Begin rendering quads.
	// This function must be called
	// before any actual rendering.
	hge->Gfx_BeginScene();

	// Clear screen with black color
	hge->Gfx_Clear(0);
	
	// Render quads here. This time just
	// one of them will serve our needs.
	//hge->Gfx_RenderQuad(&quad);

	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}
Game::~Game()
{

}