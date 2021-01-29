#include "MapManager.h"
MapManager::MapManager(HGE* hge_in, std::vector<Entity*>* mapItems_in, std::vector<Tiles*>* tiles_in, const unsigned int& width_in, const unsigned int&  height_in)
{
	hge = hge_in;
	mapItems = mapItems_in;
	tiles = tiles_in;
	width = width_in;
	height = height_in;
}
void MapManager::LoadMap(const std::string& path)
{
	std::ifstream ifs;
	ifs.open(path.c_str());
	// if file is already exist
	if(ifs.is_open())
	{
		//Reading variables
		char tempItem;
		unsigned int nOfTile = 0;
		while(!ifs.eof())
		{
			ifs>>tempItem;
			int tempNumItem = int(tempItem);
			switch (tempNumItem)
			{
			case 'O':
				if(nOfTile < width * height)
				{
					mapItems->push_back(new Obstacles(hge));
					mapItems->back()->SetPosition(tiles->at(nOfTile)->GetOrigin());
					tiles->at(nOfTile)->HaveObstacles(true);
					nOfTile++;
				}
				
				break;
			case 'F':
				if(nOfTile < width * height)
				{
					mapItems->push_back(new Food(hge));
					mapItems->back()->SetPosition(tiles->at(nOfTile)->GetOrigin());
					nOfTile++;
				}
				break;
			case 'H':
				if(nOfTile < width * height)
				{
					mapItems->push_back(new HolyFood(hge));
					mapItems->back()->SetPosition(tiles->at(nOfTile)->GetOrigin());
					nOfTile++;
				}
				break;
			case 'P':
				if(nOfTile < width * height)
				{
					mapItems->push_back(new PMStartPoint(hge));
					mapItems->back()->SetPosition(tiles->at(nOfTile)->GetOrigin());
					nOfTile++;
				}
				break;
			case 'G':
				if(nOfTile < width * height)
				{
					mapItems->push_back(new GHStartPoint(hge));
					mapItems->back()->SetPosition(tiles->at(nOfTile)->GetOrigin());
					nOfTile++;
				}
				break;
			default:
				break;

			};
		}

	}
	else
	{
		std::string error = "Unknown error while reading from file " + path;
		throw(std::exception(error.c_str()));
	}
}
MapManager::~MapManager()
{

}