#include "Tile.h"

void Tile::setType(TileType tType)
{
	type = tType;
}

char Tile::getSymbol()
{
	switch (type)
	{
	case EMPTY:
		return ' ';
		break;
	case HIT:
		return 'X';
		break;
	case MISS:
		return 'O';
		break;
	case BOAT:
		return 'B';
		break;
	case HIDDEN_BOAT:
		return ' ';
		break;
	}
}

void Tile::setBoat(Boat * boatptr)
{
	boat = boatptr;
}

TileType Tile::getType()
{
	return type;
}

Tile::~Tile()
{
}
