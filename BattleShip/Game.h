#pragma once
#include "Tile.h"
#include "Boat.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std; 

class Game
{
private:
	int size;
	Tile** myBoard;
	Tile** theirBoard;
	void addPlayerBoats();
	Boat playerBoats[5];
	int playerBoatsSunk;
	Boat aiBoats[5];
	int aiBoatsSunk;
	void addBoatsToField();
	void addBoat(Boat & boat, bool isPlayer, int boatNumber);
	bool Game::isValidTile(Point loc, bool isPlayer);
	bool isValidBoatPosition(Boat & boat, bool isPlayer);
	void addAIBoats();
	Point getRandomValidPoint(int boatSize, bool rotation);
	int getValueBetween(int min, int max);



public:
	Game(int boardSize);
	~Game();
	friend ostream& operator<<(ostream& stream, Game &game);
	void shoot(Point pos, bool isPlayer);
	void playGame();
};

