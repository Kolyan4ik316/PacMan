#ifndef MENU_H
#define MENU_H
#include "State.h"
#include "Button.h"
class Menu : public State
{
public:
	Menu(std::stack<State*>* states_in, HGE* hge_in);

	virtual void LoadResources() override;
	virtual void FreeResources() override;
	virtual ~Menu();
protected:
	virtual void UpdateBG(const float& dt);
	//Will managing our menu
	// Some resource handles
	HEFFECT				snd;
	HTEXTURE			tex;
	HTEXTURE			bgText;

	// Pointers to the HGE objects we will use
	hgeGUI				*gui;
	hgeFont				*fnt;
	hgeSprite			*spr;
	hgeSprite			*bgSpr;
};
#endif