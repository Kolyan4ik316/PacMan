#ifndef BUTTON_H
#define BUTTON_H
#include "EntryHeader.h"
class Button : public hgeGUIObject
{
public:
	Button(int _id, hgeFont *_fnt, HEFFECT _snd, float _x, float _y, float _delay, char *_title);
	virtual void	Render();
	virtual void	Update(float dt);

	virtual void	Enter();
	virtual void	Leave();
	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);


	virtual ~Button();
private:
	hgeFont		*fnt;
	HEFFECT		snd;
	float		delay;
	char		*title;

	hgeColor	scolor, dcolor, scolor2, dcolor2, sshadow, dshadow;
	hgeColor	color, shadow;
	float		soffset, doffset, offset;
	float		timer, timer2;
};
#endif