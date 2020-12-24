#ifndef STATE_H
#define STATE_H
#include "EntryHeader.h"
class State
{
public:
	State(){};
	//Update
	virtual bool Update() = 0;
	//Render
	virtual bool Render() = 0;
	
	virtual void UpdateInput(const float& dt) = 0;
	virtual void EndState() = 0;

	virtual ~State(){};
protected:

};
#endif