#ifndef BUTTON_H
#define BUTTON_H
#include "Widget.h"
class Button : public Widget
{
public:
	Button();
	void Update(const float dt) override;
	void Render(HGE *hge) override;
	virtual ~Button();
protected:
	static position pos;
};
#endif