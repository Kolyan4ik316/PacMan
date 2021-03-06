#ifndef STATE_H
#define STATE_H
#include "EntryHeader.h"
class State
{
public:
	struct DiffAtributes
	{
		unsigned int num_of_ghosts;
		float speed_of_ghosts;
		float release_delay;
		float pacMan_speed;
	};
public:
	enum Difficult : unsigned int
	{
		Easy,
		Normal,
		Hard
	};
public:
	//Ctor(takes paramaters, i'm gonna add more paramaters later)
	State(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) = 0;
	//Render
	virtual void Render() = 0;
	// Updating key states, mouse state
	virtual void UpdateInput(const float& dt) = 0;
	// function calling when we need to quit
	virtual void EndState()
	{
		quit = true;
	}
	// Function for loading resources and releasing them
	virtual void LoadResources() = 0;
	virtual void FreeResources() = 0;
	virtual void SetReoslution(const std::string& resolution);
	
	// Returning if we quit from state
	const bool& GetQuit() const
	{
		return quit;
	}
	//Dtor (need to be virtual for base class, for preventing memory leak)
	const bool& ToMainMenu()const
	{
		return toMainMenu;
	}
	const bool& CloseGame()const
	{
		return closeGame;
	}
	static void LoadDifficults(State::DiffAtributes attr);
	virtual ~State(){};
protected:
	void SetDifficult(Difficult diff)
	{
		difficult = diff;
	}
	bool toMainMenu;
	bool closeGame;
	// variable for quiting
	bool quit;
	// Pointer to stack of pointer of states
	// we can managing of states by using him
	std::stack<State*>* states;
	HGE* hge;
	static int screenWidth;
	static int screenHeight;
	
	static float originX;
	static float originY;

	static float scaleX;
	static float scaleY;

	static std::string resolut;

protected:
	static Difficult difficult;
	static std::vector<State::DiffAtributes> diffs;

};

#endif