#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PacMan.h"

class GameState : public State
{
public:
	GameState();
	void LoadResources(HGE *hge) override;
	//Update
	bool Update(HGE *hge, const float dt) override;
	//Render
	void Render(HGE *hge) override;
	
	void UpdateInput(const float dt) override;
	void EndState() override{};
	void boom(HGE* hge) 
	{
		int pan=int((x-400)/4);
		float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
		hge->Effect_PlayEx(snd,100,pan,pitch);
	};
	void FreeResources(HGE *hge);
	virtual ~GameState();
private:
	static hgeQuad quad;
	static HEFFECT snd;
	// Some "gameplay" variables and constants
	static float x,y;
	static float dx, dy;

	static const float speed;
	static const float friction;
	static bool isLoadedResources;
	static PacMan player;

};

#endif