#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include "HolyFood.h"
#include "Ghost.h"
#include "PacMan.h"
#include "GHStartPoint.h"
#include "PMStartPoint.h"
#include "Obstacles.h"
class MapManager
{
public:
	MapManager(HGE* hge_in, std::vector<Entity*>* mapItems_in, std::vector<Tiles*>* tiles_in, const unsigned int& width_in, const unsigned int&  height_in);
	void LoadMap();
	virtual ~MapManager();
private:
	std::vector<Entity*>* mapItems;
	std::vector<Tiles*>* tiles;
	unsigned int width;
	unsigned int height;
	HGE* hge;
};
#endif