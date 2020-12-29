#ifndef MAINMENU_H
#define MAINMENU_H
//#include "State.h"
#include "GameState.h"
#include "Button.h"
class MainMenu : public State
{
public:
	MainMenu(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	void Update(const float& dt) override;
	//Render
	void Render() override;
	
	void UpdateInput(const float& dt) override;
	//void EndState() override{};

	void LoadResources() override;
	void FreeResources() override;
	virtual ~MainMenu();
private:
	//Will managing our menu
	// Some resource handles
	HEFFECT				snd;
	HTEXTURE			tex;
	hgeQuad				quad;

	// Pointers to the HGE objects we will use
	hgeGUI				*gui;
	hgeFont				*fnt;
	hgeSprite			*spr;
};


#endif