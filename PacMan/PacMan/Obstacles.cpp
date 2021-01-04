#include "Obstacles.h"

Obstacles::Obstacles(HGE* hge_in)
	:
	Entity(hge_in)
{

}
void Obstacles::Update(const float& dt)
{
	rect.Set(pos.x * scaleX , pos.y * scaleY , (pos.x + 32.0f) * scaleX , (pos.y + 32.0f) * scaleY);
}
void Obstacles::Render()
{
	hgeColor color(88.0f, 147.0f, 25.0f, 0.0f);
	const hgeU32 tempColor = color.GetHWColor();
	const float offset = 5.0f;
	for(float i = 0.0f; i < offset; i++)
	{
		hge->Gfx_RenderLine(rect.x1, rect.y1 + i, rect.x2, rect.y1 + i, tempColor);
		hge->Gfx_RenderLine(rect.x1 + i, rect.y1, rect.x1 + i, rect.y2, tempColor);
		hge->Gfx_RenderLine(rect.x1, rect.y2 - i, rect.x2, rect.y2 - i, tempColor);
		hge->Gfx_RenderLine(rect.x2 - i, rect.y1, rect.x2 - i, rect.y2, tempColor);
	}
	
}
void Obstacles::Render(const float& sizeX, const float& sizeY)
{
	hgeColor color(88.0f, 147.0f, 25.0f, 0.0f);
	const hgeU32 tempColor = color.GetHWColor();
	const float offset = 5.0f;
	for(float i = 0.0f; i < offset; i++)
	{
		hge->Gfx_RenderLine(rect.x1 * sizeX, (rect.y1 + i) * sizeY, rect.x2 * sizeX, (rect.y1 + i) * sizeY, tempColor);
		hge->Gfx_RenderLine((rect.x1 + i) * sizeX, rect.y1 * sizeY, (rect.x1 + i) * sizeX, rect.y2 * sizeY, tempColor);
		hge->Gfx_RenderLine(rect.x1 * sizeX, (rect.y2 - i) * sizeY, rect.x2 * sizeX, (rect.y2 - i) * sizeY, tempColor);
		hge->Gfx_RenderLine((rect.x2 - i) * sizeX, rect.y1 * sizeY, (rect.x2 - i) * sizeX, rect.y2 * sizeY, tempColor);
	}
}
Obstacles::~Obstacles()
{

}
