#include "Game.h"
#include <map>

using namespace std;


//	2 2 1 4 3 0 7 4 1 2 5 0 2 8 0

int main()
{
	srand(time(nullptr));

	Game game(10);
	
	cout << game;
	
	game.playGame();
	system("pause");
	return 0;
}