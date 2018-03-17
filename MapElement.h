#pragma once
#define TILE_SIZE 4
#define MIN_U 0
#define MIN_V 0
#define MAX_U 1
#define MAX_V 1


class MapElement : ObjectC
{
public:
	void MapElement::init(Coord2D position);
	MapElement();
	~MapElement();
	void render();
	ColorT myColor = ColorT::NONE;
};

