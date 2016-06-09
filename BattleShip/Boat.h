#pragma once
struct Point {
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	int x, y;
};

const int availableSizes[5] = { 2, 3, 3, 4, 5 };

class Boat
{
private:
	int boatSize;
	Point* location;
	int amountOfHits = 0;
	bool isSunk = false;
	bool rotation;
public:
	Boat(int size, bool rotation, Point start);
	Boat();
	Boat(const Boat & boat);
	Point* getPos() const{ return location; }
	int getSize() const{ return boatSize; }
	bool getRotation() const{ return rotation; }
	~Boat();
	bool getHit();
};