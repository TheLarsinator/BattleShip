#include "Game.h"

using namespace std;

void Game::addPlayerBoats()
{
	Point pos;
	Boat boat;
	bool rot;
	for (int i = 0; i < 5; i++)
	{
		cout << "Boat " << i+1 << ": " << endl;
		cout << "Size: " << availableSizes[i] << endl;
		cout << "Enter the x and y coordinate, and then 1 for a rotated boat, or zero:" << endl;
		do {
			cin >> pos.x;
			cin >> pos.y;
			cin >> rot;
			pos.x--;
			pos.y--;
			boat = Boat(availableSizes[i], rot, pos);
		} while (!isValidBoatPosition(boat, true));
		addBoat(Boat(availableSizes[i], rot, pos), true, i);
		//aiBoats[i] = Boat(availableSizes[i], rot, pos);
	}
}

int Game::getValueBetween(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

Point Game::getRandomValidPoint(int boatSize, bool rotation)
{
	Point pos;
	do {
		pos.x = getValueBetween(0, size);
		pos.y = getValueBetween(0, size);
	} while (isValidBoatPosition(Boat(boatSize, rotation, pos), false));
	return pos;

}

void Game::addAIBoats()
{
	Point pos;
	Boat boat;
	bool rot;
	for (int i = 0; i < 6; i++)
	{
		do {
			rot = getValueBetween(0, 1);
			pos = getRandomValidPoint(availableSizes[i], rot);
			boat = Boat(availableSizes[i], rot, pos);
		} while (!isValidBoatPosition(boat, false));
		addBoat(boat, false, i);
	}
}

bool Game::isValidBoatPosition(Boat &boat, bool isPlayer)
{
	for (int i = 0; i < boat.getSize(); i++)
	{
			if (isPlayer)
			{
				if (!isValidTile(boat.getPos()[i], true))
				{
					cout << "Invalid postion, try again: ";
					return false;
				}
			}
			else
			{
				if (!isValidTile(boat.getPos()[i], false))
				{
					return false;
				}
			}
	}
	return true;
}

bool Game::isValidTile(Point loc, bool isPlayer)
{
	if (loc.x < this->size && loc.y < this->size)
	{
		if (isPlayer)
		{
			if (myBoard[loc.y][loc.x].getType() == EMPTY)
			{
				return true;
			}
		}
		else
		{
			if (theirBoard[loc.y][loc.x].getType() == EMPTY)
			{
				return true;
			}
		}
	}
	return false;
}

void Game::addBoatsToField()
{
	Boat *temp;
	for (int i = 0; i < 6; i++)
	{
		temp = &playerBoats[i];
		for (int j = 0; j < temp->getSize(); j++)
		{
			myBoard[temp->getPos()[j].y][temp->getPos()[j].x].setType(BOAT);
			myBoard[temp->getPos()[j].y][temp->getPos()[j].x].setBoat(&playerBoats[i]);
		}
		temp = &aiBoats[i];
		for (int j = 0; j < temp->getSize(); j++)
		{
			theirBoard[temp->getPos()[j].y][temp->getPos()[j].x].setType(HIDDEN_BOAT);
			theirBoard[temp->getPos()[j].y][temp->getPos()[j].x].setBoat(&aiBoats[i]);
		}
	}
}

void Game::addBoat(Boat &boat, bool isPlayer, int boatNumber)
{
	for (int i = 0; i < boat.getSize(); i++)
	{
		if (isPlayer)
		{
			myBoard[boat.getPos()[i].y][boat.getPos()[i].x].setType(BOAT);
			myBoard[boat.getPos()[i].y][boat.getPos()[i].x].setBoat(&boat);
			playerBoats[boatNumber] = boat;
		}
		else
		{
			theirBoard[boat.getPos()[i].y][boat.getPos()[i].x].setType(HIDDEN_BOAT);
			theirBoard[boat.getPos()[i].y][boat.getPos()[i].x].setBoat(&boat);
			aiBoats[boatNumber] = boat;
		}
	}
}

Game::Game(int boardSize) : size(boardSize)
{
	myBoard = new Tile*[size];
	theirBoard = new Tile*[size];

	for (int i = 0; i < size; i++)
	{
		myBoard[i] = new Tile[size];
		theirBoard[i] = new Tile[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			myBoard[i][j] = Tile();
			theirBoard[i][j] = Tile();
		}
	}

	cout << myBoard[2][2].getType();

	//addPlayerBoats();
	//addAIBoats();
	//addBoatsToField();
}

Game::~Game()
{
	delete[] myBoard;
	delete[] theirBoard;
	myBoard = theirBoard = nullptr;
}

void Game::shoot(Point pos, bool isPlayer)
{
	if (isPlayer)
	{
		if (theirBoard[pos.x][pos.y].getType() == BOAT || theirBoard[pos.x][pos.y].getType() == HIDDEN_BOAT)
		{
			theirBoard[pos.x][pos.y].setType(HIT);
			if (theirBoard[pos.x][pos.y].getBoat()->getHit())
			{
				aiBoatsSunk++;
			}
		}
		else
			theirBoard[pos.x][pos.y].setType(MISS);
	}
	else
	{
		if (myBoard[pos.x][pos.y].getType() == BOAT || myBoard[pos.x][pos.y].getType() == HIDDEN_BOAT)
		{
			myBoard[pos.x][pos.y].setType(HIT);
			if (myBoard[pos.x][pos.y].getBoat()->getHit())
			{
				playerBoatsSunk++;
			}
		}
		else
			myBoard[pos.x][pos.y].setType(MISS);
	}
}

void Game::playGame()
{
	while (true)
	{
		cout << "Shoot at position: (x, y); ";
		int x, y;
		cin >> x;
		cin >> y;
		shoot(Point(y-1, x-1), true);

		cout << *this;

	//	cout << "AI: " << aiBoatsSunk << "Player: " << playerBoatsSunk << endl;

		if (aiBoatsSunk == 5)
		{
			cout << "You have won the game! Well done!" << endl;
			break;
		}
		else if(playerBoatsSunk == 5)
		{
			cout << "AI won the game! Try again!" << endl;
			break;
		}
	}

}

ostream& operator<<(ostream& stream, Game &game)
{
	stream << "Opponents field: " << endl;
	stream << "    ";
	for (int i = 1; i < game.size + 1; i++)
	{
		stream << i << " ";
	}
	stream << endl;
	for (int i = 0; i < game.size; i++)
	{
		if(i+1 < 10)
			stream << i+1 << " | ";
		else
			stream << i + 1 << "| ";

		for (int j = 0; j < game.size; j++)
		{
			stream << game.theirBoard[i][j].getSymbol() << " ";
		}

		stream << " |" << endl;
	}

	stream << "Player field: " << endl;
	stream << "    ";
	for (int i = 1; i < game.size + 1; i++)
	{
		stream << i << " ";
	}
	stream << endl;
	for (int i = 0; i < game.size; i++)
	{
		if (i + 1 < 10)
			stream << i + 1 << " | ";
		else
			stream << i + 1 << "| ";

		for (int j = 0; j < game.size; j++)
		{
			stream << game.myBoard[i][j].getSymbol() << " ";
		}

		stream << " |" << endl;
	}

	return stream;
}