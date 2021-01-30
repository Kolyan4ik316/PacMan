#include "PathFinder.h"
#include <cassert>
PathFinder::Node::Node(hgeVector pos_in, hgeVector targetPos_in, int G_in, Node* parent_in)
	:
	pos(pos_in),
	targetPos(targetPos_in),
	G(G_in),
	parent(parent_in)
{
	H = int(std::abs(targetPos.x - pos.x) + std::abs(targetPos.y - pos.y));
	F = G + H;
}
PathFinder::Node::~Node()
{

}

PathFinder::PathFinder(unsigned int nMapWidth_in, unsigned int nMapHeight_in, std::vector<Tiles*>* tiles_in)
	:
	nMapWidth(nMapWidth_in),
	nMapHeight(nMapHeight_in),
	tiles(tiles_in)
{

}
std::vector<Tiles*> PathFinder::GetPath(const hgeVector& startPos,const hgeVector& target)
{
	// if position of entitie is same as target returning empty container
	if(target.x == startPos.x && target.y == startPos.y)
	{
		return pathToTarget;
	}
	// start node whiche will have parent = null
	Node* startNode = new Node(startPos, target, 0, NULL);//;
	
	// adding start to checked nodes
	checkedNodes.push_back(startNode);
	// adding to waiting for checking their neighbours
	for(unsigned int i = 0; i< GetNeighbourNodes(startNode).size(); i++)
	{
		waitingNodes.push_back(GetNeighbourNodes(startNode).at(i));
	}
	// while we don't check all waiting nodes
	while(!waitingNodes.empty())
	{
		// creating temp node where is gonna be magic
		Node* curNode = NULL;
		// sorting waiting nodes by less F
		std::sort(waitingNodes.begin(), waitingNodes.end(), LessFValue);
		// checking the most less F nodes what is in waiting nodes
		curNode = waitingNodes.front();
		// if current node position is same as target, we are gonna to calculate them
		if(curNode->pos.x == target.x && curNode->pos.y == target.y)
		{
			// vector of tiles which we gonna return
			std::vector<Tiles*> tempVector;
			//calculating
			std::vector<hgeVector> tempVecVector = CalculatePathFromNode(curNode);
			for (unsigned int i = 0; i < tempVecVector.size(); i++ )
			{
				// pushing by using sweet function putpixel:) y * width + x
				tempVector.push_back((*tiles).at(unsigned int(tempVecVector.at(i).y * nMapWidth  + tempVecVector.at(i).x)));
			}
			return tempVector;
		}
		// if tile by node position have obstacles
		// erasing this node from waiting, we are not gonna to calculate them
		if((*tiles).at(unsigned int(curNode->pos.y * nMapWidth  + curNode->pos.x))->ObstaclesInside())
		{
			std::swap(waitingNodes.front(), waitingNodes.back());
			waitingNodes.pop_back();
			// adding this node to checked
			checkedNodes.push_back(curNode);
		}
		else
		{
			// erasing this node from waiting, we are gonna to check their neighbour
			std::swap(waitingNodes.front(), waitingNodes.back());
			waitingNodes.pop_back();
			if(!IsExist(&checkedNodes, curNode))
			{
				checkedNodes.push_back(curNode);
				for(unsigned int j = 0; j< GetNeighbourNodes(curNode).size(); j++)
				{
					waitingNodes.push_back(GetNeighbourNodes(curNode).at(j));
				}
			}
			
		}
	}
	
	return pathToTarget;
}
void PathFinder::CleanUpNodes()
{
	// Free memory
	while(!checkedNodes.empty())
	{
		if(checkedNodes.back())
		{
			assert(checkedNodes.back()->targetPos.x >= 0.0f || checkedNodes.back()->targetPos.y >= 0.0f);
			delete checkedNodes.back();
			checkedNodes.back() = NULL;
		}
		checkedNodes.pop_back();
	}
	while(!pathToTarget.empty())
	{
		if(pathToTarget.back())
		{
			delete pathToTarget.back();
			pathToTarget.back() = NULL;
		}
		pathToTarget.pop_back();
	}
	while(!waitingNodes.empty())
	{
		if(waitingNodes.back())
		{
			delete waitingNodes.back();
			waitingNodes.back() = NULL;
		}
		waitingNodes.pop_back();
	}
}
std::vector<hgeVector> PathFinder::CalculatePathFromNode(Node* node)
{
	std::vector<hgeVector> calcPath;
	// temp variables
	Node* curNode = node;
	hgeVector tempPos;
	// if current node have parent
	while(curNode->parent)
	{
		// to temporary setting node position
		tempPos = curNode->pos;
		// pushing them
		calcPath.push_back(tempPos);
		// setting to temp node parant of them
		curNode = curNode->parent;

	}
	return calcPath;
	
}
std::vector<Node*> PathFinder::GetNeighbourNodes(Node* node)
{
	// returning neighbours
	std::vector<Node*> vecNeighbours;
	
	vecNeighbours.push_back(new Node(hgeVector(node->pos.x - 1, node->pos.y), node->targetPos, node->G + 1, node));
	
	vecNeighbours.push_back(new Node(hgeVector(node->pos.x + 1, node->pos.y), node->targetPos, node->G + 1, node));

	vecNeighbours.push_back(new Node(hgeVector(node->pos.x, node->pos.y - 1), node->targetPos, node->G + 1, node));
	
	vecNeighbours.push_back(new Node(hgeVector(node->pos.x, node->pos.y + 1), node->targetPos, node->G + 1, node));

	return vecNeighbours;
}

PathFinder::~PathFinder()
{
	CleanUpNodes();
}