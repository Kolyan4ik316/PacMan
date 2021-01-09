#include "PathFinder.h"
PathFinder::PathFinder(unsigned int nMapWidth_in, unsigned int nMapHeight_in, std::vector<Tiles*>* tiles_in)
	:
	nMapWidth(nMapWidth_in),
	nMapHeight(nMapHeight_in),
	tiles(tiles_in)
{

}
float PathFinder::Distance(Tiles* a, Tiles* b)
{
	return sqrtf((a->pos.x - b->pos.x) * (a->pos.x - b->pos.x) + (a->pos.y - b->pos.y) * (a->pos.y - b->pos.y));
}
float PathFinder::Heuristic(Tiles* a, Tiles* b)
{
	return Distance(a, b);
}
void PathFinder::SolveA_Star(DynamicEntity* explorer)
{
	if(explorer->TimeForSolvingWasReached()) 
	{
		// Reset Navigation Graph - default all node states
		for (unsigned int x = 0; x < nMapWidth; x++)
		{
			for (unsigned int y = 0; y < nMapHeight; y++)
			{
				(*tiles)[y * nMapWidth + x]->bVisited = false;
				(*tiles)[y * nMapWidth + x]->fGlobalGoal = FLT_MAX;
				(*tiles)[y * nMapWidth + x]->fLocalGoal = FLT_MAX;
				(*tiles)[y * nMapWidth + x]->parent = NULL;	// No parents
			}
		}
		Tiles* nodeCurrent = explorer->nodeStart;
		explorer->nodeStart->fLocalGoal = 0.0f;
		explorer->nodeStart->fGlobalGoal = Heuristic(explorer->nodeStart, explorer->nodeEnd);

		std::list<Tiles*> listNotTestedNodes;
		listNotTestedNodes.push_back(explorer->nodeStart);
		while (!listNotTestedNodes.empty() && nodeCurrent != explorer->nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
		{
			listNotTestedNodes.sort(LessfGlobalGoal);
		
			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			{
				listNotTestedNodes.pop_front();
			}
			if (listNotTestedNodes.empty())
			{
				break;
			}
			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true; // We only explore a node once	
			for (unsigned int i = 0; i <nodeCurrent->vecNeighbours.size(); i++)
			{
				if (!nodeCurrent->vecNeighbours.at(i)->bVisited && nodeCurrent->vecNeighbours.at(i)->ObstaclesInside() == false)
				{
					listNotTestedNodes.push_back(nodeCurrent->vecNeighbours.at(i));
				}
				float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + Distance(nodeCurrent, nodeCurrent->vecNeighbours.at(i));
				if (fPossiblyLowerGoal < nodeCurrent->vecNeighbours.at(i)->fLocalGoal)
				{
					nodeCurrent->vecNeighbours.at(i)->parent = nodeCurrent;
					nodeCurrent->vecNeighbours.at(i)->fLocalGoal = fPossiblyLowerGoal;
					
					
					nodeCurrent->vecNeighbours.at(i)->fGlobalGoal = nodeCurrent->vecNeighbours.at(i)->fLocalGoal + Heuristic(nodeCurrent->vecNeighbours.at(i), explorer->nodeEnd);
					
				}
			}
		}
		explorer->ResetTimeForSolving();
	}
	

}
PathFinder::~PathFinder()
{

}