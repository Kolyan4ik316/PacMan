#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "EntryHeader.h"
#include "Tiles.h"
#include "Ghost.h"
class PathFinder
{
public:
	struct Node
	{
		Node(hgeVector pos_in, hgeVector targetPos_in, int G_in, Node* parent_in);
		int F;
		int G;
		int H;
		Node* parent;
		hgeVector pos;
		hgeVector targetPos;
		~Node();
	};
		
public:
	PathFinder(unsigned int nMapWidth_in, unsigned int nMapHeight_in, std::vector<Tiles*>* tiles_in);
	virtual std::vector<Tiles*> GetPath(const hgeVector& startPos, const hgeVector& target);
	virtual std::vector<hgeVector> CalculatePathFromNode(Node* node);
	void CleanUpNodes();
	static bool LessFValue(Node* rhs, Node* lhs)
	{
		return rhs->F < lhs->F;
	}
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
	std::vector<Tiles*> pathToTarget;
	std::vector<Tiles*>* tiles;
	std::vector<Node*> GetNeighbourNodes(Node* node);
private:
	std::vector<Node*> checkedNodes;
	std::vector<Node*> waitingNodes;
	unsigned int nMapWidth;
	unsigned int nMapHeight;
};
typedef PathFinder::Node Node;

#endif