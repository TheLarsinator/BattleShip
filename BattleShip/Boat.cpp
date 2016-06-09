#include "Boat.h"
#include <iostream>
using namespace std;

Boat::Boat(const Boat &boat) : boatSize(boat.getSize()), rotation(boat.getRotation())
{
	for (int i = 0; i < boatSize; i++)
	{
		location[i] = boat.getPos()[i];
	}
}

Boat::Boat(int size, bool rotation, Point start) : boatSize(size), rotation(rotation)
{
	location = new Point[size];
	location[0] = start;
	for (int i = 1; i < size; i++)
	{
		if (!rotation)
			location[i] = Point(start.x + i, start.y);
		else
			location[i] = Point(start.x, start.y + i);
	}
}

Boat::Boat() : boatSize(0), location(nullptr)
{

}

Boat::~Boat()
{
	delete[] location;
	location = nullptr;
}

bool Boat::getHit()
{
	amountOfHits++;
	if (amountOfHits == boatSize)
	{
		isSunk = true;
		cout << "A ship with the size " << boatSize << " has been sunk!" << endl;
		system("pause");
	}

	return isSunk;
}
