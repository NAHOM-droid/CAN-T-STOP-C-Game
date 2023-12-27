#include "Game.hpp"
#include "enum.hpp"
//------------------------------------------------------
Game::Game(): board(make_unique<Board>()){
	state = Status::begun;
	if (strcmp(DICE, "FAKE") == 0) {
		input.open(FILE_NAME);
		if(!input.is_open()) fatal("File couldn't be opened.");
		dice = make_unique<FakeDice>();
	} else dice = make_unique<CantStopDice>();
}
//--------------------------------------------------------
Status Game::oneTurn(Player* pp) {
	board->startTurn(pp);
	cout << *board<<endl;
	for (;;) {
		try {
			char playerChoice = getPlayerChoice();
			if (choices.find(playerChoice) == string::npos) throw BadChoice();
			if (playerChoice == 's') { board->stop(); return Status::begun;}
			else if (playerChoice == 'r') {
				const int* dicePairs;
				if (typeid(*dice.get()) == typeid(FakeDice)) dicePairs = ((FakeDice*)dice.get())->roll(input);
				else dicePairs = dice->roll();
				cout << dicePairs[0] << " " << dicePairs[1] << endl;
				bool moves = board->move(dicePairs[0]) | board->move(dicePairs[1]);
				if (!moves) { board->bust(); return Status::begun;}
				cout << endl << *board << endl;
			}else{
				board->quit();
				playersList.remove();
				cout<<"Player Quit." << endl;
				return Status::quit;
			}
		} catch (BadChoice& b) {b.print();}
	}
	return Status::begun;
}
//-----------------------------------------------------------------------------------------------
char Game::getPlayerChoice(){
	char playerChoice;
	if (typeid(*dice.get()) == typeid(FakeDice)){
		input >> playerChoice;
		if(input.eof()) fatal("End of File");
		cout<<"Player Choice: " << playerChoice <<endl;
	}
	else{
		cout << "Press r to roll, s to stop, q to resign: ";
		cin >> playerChoice;
	}
	return playerChoice;
}
//------------------------------------------------------------------------------------------------
void Game::play() {
	playersList.init();
	cout<<"\n\t\t\tSCORE BOARD\n" << playersList;
	Player* currentP;
	while (state == Status::begun) {
		currentP = playersList.getCurrent();
		cout <<endl<< currentP->Name() << "'s turn==>"<< endl;
		Status CS = oneTurn(currentP);
		if (currentP->Score() == 3){ state = Status::done; board->startTurn(nullptr);}
		else if(playersList.count() == 0) state = Status::quit;
		else if(CS == Status::begun ) playersList++;
	}
	if (state == Status::done)
		cout <<"\t\t\tSCORE BOARD\n" <<endl << *board << endl << playersList << endl
				             << currentP->Name()<< " is the winner :)\n";
	else cout << "Game quit.\n";
	input.close();
}
//-----------------------------------------------------------------------------------------------
void Game::getPlayers(){
	cout << "\t\t\t!!!Starting Game!!!" << endl;
	cout << "Choose number of Players ( 2 - 4 ): ";
	int playerCount;
	cin >> playerCount;
	//default 2 players;
	playerCount = (playerCount > 4 || playerCount < 2)? 2 : playerCount;
	for (int k = 1; k <= playerCount; ) {
		cout<<"Player #"<< k <<endl;
		try{
		    playersList.addCell(getNewPlayer());
			k++;
		}catch(BadPlayer& b){ b.print();}
	}
}

//------------------------------------------------------------------------------------------------
Player* Game::getNewPlayer(){
	string name = getPlayerName();
	char c = getPlayerColor();
	int len = playersList.count();
	bool checkName = false;
	playersList.init();
	for(int k=0;k<len;k++) if(name == playersList.next()->Name()) checkName = true;
	bool checkColor = freeColors.find(c) == string::npos;
	if(checkName && checkColor)throw BadPlayer(name, c);
	if(checkName) throw BadName(name, c);
	if(checkColor) throw BadColor(name, c);
	freeColors[freeColors.find(c)] = '_';
	EColor color;
	switch (c) {
	case 'o': color = EColor::orange; break;
	case 'y': color = EColor::yellow; break;
	case 'g': color = EColor::green; break;
	default: color = EColor::blue;
	}
	return new Player(name, color);
}
//--------------------------------------------------------------------
string Game::getPlayerName(){
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter Name of Player: ";
	string name;
	getline(cin, name);
	int pos = name.find(" ");
	name = (pos > 0) ? name.substr(0, pos) : name;
	return name;
}
//--------------------------------------------------------------------
char Game::getPlayerColor() {
	cout << "Choose color (";
	for (int k = 0; k < 4; k++)
		if (freeColors[k] != '_')
			cout << freeColors[k] << " for " << Ecolors[k + 1] << ", ";
	cout << "): ";
	char c;
	cin >> c;
	return c;
}
//---------------------------------------------------------------------------------------------
void Game::startGame(){
	getPlayers();
	play();
}


