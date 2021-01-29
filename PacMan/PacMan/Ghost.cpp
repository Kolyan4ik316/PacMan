#include "Ghost.h"
Ghost::Ghost(HGE* hge_in)
	:
	DynamicEntity(hge_in)
{
	speed = 50.0f;
	LoadResources();
	angle = 0.0f;
	animation.back()->Play();
	currAnim = GhostAnimation::LeftRight;
	prevAnim = currAnim;
	canSolve = 0.0f;
	releaseTime = 0.0f;
	canBeAtacket = false;
	wasAtattacked = false;
	pathFinder = NULL;
}
void Ghost::LoadResources()
{
	tex=hge->Texture_Load("pacman.png");
	if(!tex)
	{
		throw(std::exception("Can't find pacman.png"));
	}
	animation.push_back(new hgeAnimation(tex, 2, 6, 2, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
	animation.push_back(new hgeAnimation(tex, 2, 6, 35, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
	animation.push_back(new hgeAnimation(tex, 2, 6, 70, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
	animation.push_back(new hgeAnimation(tex, 2, 6, 206, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
	animation.push_back(new hgeAnimation(tex, 1, 6, 256, 17, 16, 16)); 
	animation.back()->SetHotSpot(7,7);
}
void Ghost::SetPathFinder(PathFinder* pathFinder_in)
{
	

	pathFinder = pathFinder_in;
}
void Ghost::ChoseAnimation()
{
	
	if(!CanBeAtacket() && !WasAttacked())
	{
		if(std::abs(destination.x) > std::abs(destination.y))
		{
			currAnim = GhostAnimation::LeftRight;
		}
		else
		{
			if(destination.y > 0.0f)
			{
				currAnim = GhostAnimation::Top;
			}
			else
			{
				currAnim = GhostAnimation::Bottom;
			}
		}
		
	}
	else if (CanBeAtacket() && !WasAttacked())
	{
		currAnim = GhostAnimation::Scary;
	}
	else if(WasAttacked())
	{
		currAnim = GhostAnimation::Attacked;
	}
	
	if(prevAnim != currAnim)
	{
		animation.at(unsigned int(prevAnim))->Stop();
		animation.at(unsigned int(currAnim))->Play();
	}
}
void Ghost::SetDestination(const hgeVector& pos_in)
{
	goal = pos_in;
	//RenderLineToGoal();
	destination.x = std::abs(pos.x) - std::abs(pos_in.x);
	destination.y =  std::abs(pos.y) - std::abs(pos_in.y);

	ChoseAnimation();
	if(pos.x < pos_in.x)
	{
		animation.at(0)->SetFlip(true, false, true);	
		//pos.x += speed * dt;
	}
	if(pos.x > pos_in.x)
	{
		animation.at(0)->SetFlip(false, false, true);
		//pos.x -= speed * dt;
	}
	
}
void Ghost::SetPathTo(const hgeVector& target)
{
	if(canSolve >= 0.5f)
	{
		pathToTarget = pathFinder->GetPath(pos_tile, target);
		ResetTimeForSolving();
		
	}
	if(canSolve <= 0.5f)
	{
		pathFinder->CleanUpNodes();
	}
}
Tiles* Ghost::GetNextPosition()
{
	return pathToTarget.back();
}
void Ghost::Update(const float& dt)
{
	if(!pathToTarget.empty())
	{
		if(pos_tile == GetNextPosition()->GetPosition())
		{
			pathToTarget.pop_back();
		}
	}
	pos.x+=dir.x * speed * scaleX * dt;
	pos.y+=dir.y * speed * scaleY * dt;

	rect.Set(pos.x - (12.0f * scaleX), pos.y - (12.0f * scaleY), pos.x + (12.0f * scaleX), pos.y + (12.0f * scaleY));
	animation.at(unsigned int(currAnim))->Update(dt);
	prevAnim = currAnim;
	canSolve += dt;
}
void Ghost::SwitchAtacked()
{
	canBeAtacket = !canBeAtacket;
}
bool Ghost::WasAttacked()
{
	return wasAtattacked;
}
void Ghost::SwitchWasAtacked()
{
	wasAtattacked = !wasAtattacked;
}
bool Ghost::CanBeAtacket()
{
	return canBeAtacket;
}
void Ghost::Render()
{
	animation.at(unsigned int(currAnim))->RenderEx(pos.x, pos.y, angle, scaleX * 1.7f, scaleY* 1.7f);
	//hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y2);
}
/*void Ghost::Render(const float& sizeX, const float& sizeY)
{
	animation.at(unsigned int(currAnim))->RenderEx(pos.x, pos.y, angle, sizeX * 2.0f, sizeY * 2.0f);
}*/
void Ghost::RenderLineToGoal()
{
	hge->Gfx_RenderLine(rect.x1, rect.y1, goal.x, goal.y);
}
void Ghost::FreeResources()
{
	hge->Texture_Free(tex);
}
Ghost::~Ghost()
{
	if(pathFinder)
	{
		delete pathFinder;
	}
	FreeResources();
}