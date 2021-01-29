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
	if(target.x == startPos.x && target.y == startPos.y)
	{
		return pathToTarget;
	}
	Node* startNode = new Node(startPos, target, 0, NULL);//;

	checkedNodes.push_back(startNode);
	for(unsigned int i = 0; i< GetNeighbourNodes(startNode).size(); i++)
	{
		waitingNodes.push_back(GetNeighbourNodes(startNode).at(i));
	}
	while(!waitingNodes.empty())
	{
		Node* curNode = NULL;
		std::sort(waitingNodes.begin(), waitingNodes.end(), LessFValue);
		curNode = waitingNodes.front();
		if(curNode->pos.x == target.x && curNode->pos.y == target.y)
		{
			/*if(startNode)
			{	
				delete startNode;
				startNode = NULL;
			}*/
			std::vector<Tiles*> tempVector;
			std::vector<hgeVector> tempVecVector = CalculatePathFromNode(curNode);
			for (unsigned int i = 0; i < tempVecVector.size(); i++ )
			{
				tempVector.push_back((*tiles).at(unsigned int(tempVecVector.at(i).y * nMapWidth  + tempVecVector.at(i).x)));
			}
			return tempVector;
		}
		if((*tiles).at(unsigned int(curNode->pos.y * nMapWidth  + curNode->pos.x))->ObstaclesInside())
		{
			std::swap(waitingNodes.front(), waitingNodes.back());
			waitingNodes.pop_back();
			checkedNodes.push_back(curNode);
		}
		else
		{
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
	/*while(!checkedNodes.empty())
	{
		if(checkedNodes.back())
		{
			delete checkedNodes.back();
			checkedNodes.back() = NULL;
		}
		checkedNodes.pop_back();
	}*/
	//delete startNode;
	/*if(startNode)
	{	
		delete startNode;
		startNode = NULL;
	}*/
	
	return pathToTarget;
}
void PathFinder::CleanUpNodes()
{
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
	Node* curNode = node;
	hgeVector tempPos;
	
	while(curNode->parent)
	{
		tempPos = curNode->pos;
		calcPath.push_back(tempPos);
		curNode = curNode->parent;

	}
	/*while(!checkedNodes.empty())
	{
		delete checkedNodes.back();
		checkedNodes.back() = NULL;
		checkedNodes.pop_back();
	}*/
	return calcPath;
	
}
std::vector<Node*> PathFinder::GetNeighbourNodes(Node* node)
{
	std::vector<Node*> vecNeighbours;
	
	//if(node->pos.x > 0)
	{
		vecNeighbours.push_back(new Node(hgeVector(node->pos.x - 1, node->pos.y), node->targetPos, node->G + 1, node));
	}
	//if(node->pos.x < nMapHeight - 1)
	{
		vecNeighbours.push_back(new Node(hgeVector(node->pos.x + 1, node->pos.y), node->targetPos, node->G + 1, node));
	}

	//if(node->pos.y > 0)
	{
		vecNeighbours.push_back(new Node(hgeVector(node->pos.x, node->pos.y - 1), node->targetPos, node->G + 1, node));
	}
	
	//if (node->pos.y < nMapHeight - 1)
	{
		vecNeighbours.push_back(new Node(hgeVector(node->pos.x, node->pos.y + 1), node->targetPos, node->G + 1, node));
	}

	return vecNeighbours;
}
void PathFinder::Render()
{
	/*for(unsigned int i = 0; i < pathToTarget.size(); i++)
	{
		pathToTarget.at(i)->RenderChosen();
	}
	for(unsigned int i = 0; i < checkedNodes.size(); i++)
	{
		(*tiles).at(unsigned int(checkedNodes.at(i)->pos.y * nMapWidth  + checkedNodes.at(i)->pos.x))->Render();
	}*/
	(*tiles).at(unsigned int(7 * nMapWidth  + 16))->Render();
}

PathFinder::~PathFinder()
{
	CleanUpNodes();
}