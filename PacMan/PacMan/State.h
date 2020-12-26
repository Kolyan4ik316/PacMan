#ifndef STATE_H
#define STATE_H
#include "EntryHeader.h"
class State
{
public:
	State(){};
	//Update
	virtual bool Update(HGE *hge, const float& dt) = 0;
	//Render
	virtual void Render(HGE *hge) = 0;
	
	virtual void UpdateInput(HGE *hge, const float& dt) = 0;
	virtual void EndState() = 0;

	virtual void LoadResources(HGE *hge) = 0;
	virtual void FreeResources(HGE *hge) = 0;

	virtual ~State(){};
protected:
};
#endif