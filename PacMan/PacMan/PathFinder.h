#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "EntryHeader.h"
#include "Tiles.h"
#include "Ghost.h"
class PathFinder
{
public:
	PathFinder(unsigned int nMapWidth_in, unsigned int nMapHeight_in, std::vector<Tiles*>* tiles_in);
	void SolveA_Star(DynamicEntity* explorer);
	static float Distance(Tiles* a, Tiles* b);
	static float Heuristic(Tiles* a, Tiles* b);
	virtual ~PathFinder();
	static bool LessfGlobalGoal(const Tiles* lhs, const Tiles* rhs)
	{
		return lhs->fGlobalGoal < rhs->fGlobalGoal;
	}
	static bool LessfLocalGoal(const Tiles* lhs, const Tiles* rhs)
	{
		return std::fabs(lhs->fLocalGoal)< std::fabs(rhs->fLocalGoal);
	}
private:
	unsigned int nMapWidth;
	unsigned int nMapHeight;
	std::vector<Tiles*>* tiles;
	
};


#endif