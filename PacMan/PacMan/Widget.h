#ifndef WIDGET_H
#define WIDGET_H
#include "EntryHeader.h"
class Widget
{
public:
	Widget();
	virtual bool Update(const float dt) = 0;
	virtual bool Render(HGE *hge) = 0;
	virtual ~Widget();
};
#endif