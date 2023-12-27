#pragma once
#include "Dice.hpp"
#include "Player.hpp"
#include "Column.hpp"
#include "Board.hpp"
#include "CList.hpp"
#include "BadPlayer.hpp"
#include "BadChoice.hpp"
#define FILE_NAME "fakeDiceValues.txt"
//#define DICE "FAKE"  // for fake dice values
#define DICE ""  // for canstop dice values
//----------------------------------------------------------
class Game {
private:
	unique_ptr<Dice> dice;
	int dicePairs[2]={0};
	CList<Player*> playersList;
	unique_ptr<Board> board;
	Status state;
	string freeColors = "oygb";
	const string choices = "rsq"; // for roll, stop and quit
	ifstream input;
	Status oneTurn(Player*);
	char getPlayerChoice();
	Player* getNewPlayer();
	string getPlayerName();
	char getPlayerColor();
	void getPlayers();
	void play();
public:
	Game();
	~Game() = default;
	void startGame();
};

