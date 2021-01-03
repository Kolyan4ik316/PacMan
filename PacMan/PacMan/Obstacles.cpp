#include "Obstacles.h"

Obstacles::Obstacles(HGE* hge_in)
	:
	Entity(hge_in)
{

}
void Obstacles::Update(const float& dt)
{
	rect.Set(pos.x, pos.y, pos.x + 32.0f, pos.y + 32.0f);
}
void Obstacles::Render()
{
	hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y1);
	hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x1, rect.y2);
	hge->Gfx_RenderLine(rect.x1, rect.y2, rect.x2, rect.y2);
	hge->Gfx_RenderLine(rect.x2, rect.y1, rect.x2, rect.y2);
}
Obstacles::~Obstacles()
{

}
