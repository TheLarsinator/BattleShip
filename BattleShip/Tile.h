#pragma once
#include "Boat.h"

enum TileType
{
	EMPTY, HIT, MISS, BOAT, HIDDEN_BOAT
};

class Tile
{
private:
	TileType type;
	Boat* boat;
public:
	Tile() : type(EMPTY) {}
	TileType getType();
	void setType(TileType tType);
	char getSymbol();
	void setBoat(Boat* boat);
	Boat* getBoat() { return boat; }
	~Tile();
};

