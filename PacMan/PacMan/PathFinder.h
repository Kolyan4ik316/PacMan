#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "EntryHeader.h"
#include "Tiles.h"
#include "Ghost.h"
class PathFinder
{
public:
	// A* node 
	struct Node
	{
		Node(hgeVector pos_in, hgeVector targetPos_in, int G_in, Node* parent_in);
		int F; // H + G
		int G; // distance from start position to node itself
		int H; // distance from node itself to target
		Node* parent;
		// node position of itself
		hgeVector pos;
		// node position of target
		hgeVector targetPos;
		~Node();
	};
		
public:
	// ctor
	PathFinder(unsigned int nMapWidth_in, unsigned int nMapHeight_in, std::vector<Tiles*>* tiles_in);
	// main function for getting vector of tiles where entity should go
	virtual std::vector<Tiles*> GetPath(const hgeVector& startPos, const hgeVector& target);
	// calculating path
	virtual std::vector<hgeVector> CalculatePathFromNode(Node* node);
	// cleaning memory from nodes
	void CleanUpNodes();
	// function for sorting nodes
	static bool LessFValue(Node* rhs, Node* lhs)
	{
		return rhs->F < lhs->F;
	}
	// checking if node is already exists
	const bool IsExist(std::vector<Node*>* rhs, Node* nodeForChek) const
	{
		for(unsigned int i = 0; i < rhs->size(); i++)
		{
			
			if(rhs->at(i)->pos.x == nodeForChek->pos.x && rhs->at(i)->pos.y == nodeForChek->pos.y)
			{
				return true;
			}
			
		}
		return false;
	}
	virtual ~PathFinder();
private:
	// null
	std::vector<Tiles*> pathToTarget;
	// pointer to vector of tiles, need for returning GetPath()
	std::vector<Tiles*>* tiles;
	// function which will adding neighbours
	std::vector<Node*> GetNeighbourNodes(Node* node);
private:
	std::vector<Node*> checkedNodes;
	std::vector<Node*> waitingNodes;
	unsigned int nMapWidth;
	unsigned int nMapHeight;
};
typedef PathFinder::Node Node;

#endif