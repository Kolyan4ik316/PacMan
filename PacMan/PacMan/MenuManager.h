#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include "EntryHeader.h"
class MenuManager : public hgeGUIObject
{
public:
	MenuManager();
	void Update(const float& dt);
	void Render() override;
	virtual ~MenuManager();
private:
	static std::list<hgeGUIText> texts;
	static std::list<hgeGUIButton> buttons;
};
#endif