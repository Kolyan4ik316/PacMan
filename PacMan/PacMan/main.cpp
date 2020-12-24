#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Game game;
		game.Run();
	}
	catch(std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	catch(...)
	{
		MessageBoxA(NULL, "Unknown error", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	return 0;
}
